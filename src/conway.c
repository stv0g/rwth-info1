#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>

/* configuration */
#define CELL_CHAR '#'
#define CURSOR_CHAR 'X'
#define ESC 27
#define FRAME_RATE 17

/* start pattern */
uint8_t start[3][3] =  {
	{0, 1, 1},
	{1, 1, 0},
	{0, 1, 0}
};

uint8_t glider[3][3] =  {
	{0, 1, 0},
	{0, 0, 1},
	{1, 1, 1}
};

struct cursor {
	uint8_t x;
	uint8_t y;
};

void clean_world(uint8_t ** world, uint8_t width, uint8_t height) {
	int a;	
	for (a = 0; a < width; a++) {	
		memset(world[a], 0, height * sizeof(uint8_t));
	}
}

uint8_t ** create_world(uint8_t width, uint8_t height) {
	uint8_t ** world = malloc(width * sizeof(uint8_t *));
	int a;
	for (a = 0; a < width; a++) {
		world[a] = malloc(height * sizeof(uint8_t));
		if (world[a] == NULL) {
			endwin();
			fprintf(stderr, "Cant allocate memory!\n");
			exit(-1);
		}
	}

	clean_world(world, width, height);

	return world;
}

void destroy_world(uint8_t ** world, uint8_t width) {
	uint8_t a;

	for (a = 0; a < width; a++) {
		free(world[a]);
	}
	free(world);
}

void inhabit_world(uint8_t pattern[3][3], uint8_t x, uint8_t y, uint8_t ** world) {
	uint8_t a, b;

	for (a = 0; a < 3; a++) {
		for (b = 0; b < 3; b++) {
			world[x+b][y+a] = pattern[a][b];
		}
	}
}

uint8_t calc_cell_count(uint8_t ** world, uint8_t width, uint8_t height) {
	int cell_count = 0;
	uint8_t a, b;

	for (a = 0; a < width; a++) {
		for (b = 0; b < height; b++) {
			cell_count += (world[a][b]) ? 1 : 0;
		}
	}

	return cell_count;
}

uint8_t calc_cell_neighbours(uint8_t x, uint8_t y, uint8_t ** world, uint8_t width, uint8_t height) {
	uint8_t neighbours = 0;
	int a, b;

	for (a = x-1; a <= x+1; a++) {
		for (b = y-1; b <= y+1; b++) {
			if (a == x && b == y)
				continue;

			if (a >= 0 && b >= 0 &&
			    a < width && b < height) {
				neighbours += (world[a][b] > 0) ? 1 : 0;
			}
		}
	}

	return neighbours;
}

uint8_t calc_next_cell_gen(uint8_t x, uint8_t y, uint8_t ** world, uint8_t width, uint8_t height) {
	fflush(stdout);
	uint8_t neighbours = calc_cell_neighbours(x, y, world, width, height);
	uint8_t alive = world[x][y];

	if (alive) {
		if (neighbours > 3 || neighbours < 2) {
			return 0; /* died by over-/underpopulation */
		}
		else {				
			return neighbours;
		}
	}
	else if (neighbours == 3) {
		return neighbours;
	}
	else {
		return 0;
	}
}

void calc_next_gen(uint8_t ** world, uint8_t ** next_gen, uint8_t width, uint8_t height) {
	uint8_t x, y;

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			next_gen[x][y] = calc_next_cell_gen(x, y, world, width, height);
		}
	}

	/* copy world */
	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			world[x][y] = next_gen[x][y];
		}
	}
}

void print_world(uint8_t ** world, uint8_t width, uint8_t height) {
	uint8_t x, y;
	move(0, 0); /* reset cursor */

	/* cells */
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			printw("%c", (world[x][y] > 0) ? CELL_CHAR : ' ');
		}
	}
}

void print_cursor(uint8_t ** world, struct cursor cur) {
	uint8_t color = (world[cur.x][cur.y]

	move(cur.y, cur.x);
	attron(COLOR_PAIR(1));
	addch(CURSOR_CHAR);
	attroff(COLOR_PAIR(1));
}

WINDOW * init_screen() {
	WINDOW * win = initscr();
	noecho();
	timeout(0);
	keypad(win, 1);
	mousemask(BUTTON1_CLICKED, NULL);
	mouseinterval(200);
	curs_set(0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);

	return win;
}

int main(int argc, char * argv[]) {
	WINDOW * win = init_screen();
	MEVENT event;

	struct cursor cur = {0, 0};

	int generation = 0;
	uint8_t width, height, paused = 1;
	uint8_t ** world, ** next_gen;

	getmaxyx(win, height, width);

	/* initialize world */
	world = create_world(width, height);
	next_gen = create_world(width, height);

	inhabit_world(start, width/2, height/2, world);

	/* simulation loop */
	while(1) {
		/* handle events */
		switch (getch()) {
			case 'q':
				endwin();
				exit(0);
				break;

			case 'p':
				paused ^= 1;
				break;

			case 'c':
				clean_world(world, width, height);
				break;

			case 'g':
				inhabit_world(glider, cur.x, cur.y, world);
				break;

			case ' ':
				world[cur.x][cur.y] = (world[cur.x][cur.y]) ? 0 : 1;
				break;

			case KEY_MOUSE:
				if (getmouse(&event) == OK && event.bstate & BUTTON1_CLICKED) {
					cur.x = event.x;
					cur.y = event.y;
					world[cur.x][cur.y] = (world[cur.x][cur.y]) ? 0 : 1;
				}
				break;

			case KEY_UP:
				if (cur.y > 0) {
					cur.y--;
				}
				break;

			case KEY_DOWN:
				if (cur.y < height-1) {
					cur.y++;
				}
				break;

			case KEY_LEFT:
				if (cur.x > 0) {
					cur.x--;
				}
				break;

			case KEY_RIGHT:
				if (cur.x < width-1) {
					cur.x++;
				}
				break;
		}

		if (!paused) {
			usleep((float) 1 / FRAME_RATE * 1000000); /* sleep */
			calc_next_gen(world, next_gen, width, height);
			generation++;
		}

		print_world(world, width, height);
		print_cursor(world, cur);

		attron(COLOR_PAIR(2));
		mvprintw(0, 0, "generation: %d\tcells: %d framerate: %d fps\twidth: %d\theight: %d cursor: (%d|%d)\n", generation, calc_cell_count(world, width, height), FRAME_RATE, width, height, cur.x, cur.y);
		if (paused) mvprintw(0, width-6, "PAUSED");
		attroff(COLOR_PAIR(2));

		refresh();
	}

	endwin();
	return 0;
}
