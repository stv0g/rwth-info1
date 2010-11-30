/**
 * C implementation of Conway's Game of Life
 *
 * Grundlagen Informatik 1, 30.11.2010, RWTH Aachen
 * based on libncurses
 *
 * @author Steffen Vogel <info@steffenvogel.de>
 * @copyright Copyright (c) 2010, Steffen Vogel
 * @license http://opensource.org/licenses/gpl-license.php GNU Public License
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>

/* configuration */
#define CURSOR_CHAR '#'

struct pattern {
	uint8_t width;
	uint8_t height;
	uint8_t * data;
};

struct cursor {
	uint8_t x;
	uint8_t y;
};

uint8_t start[3][3] = {
	{0, 1, 1},
	{1, 1, 0},
	{0, 1, 0}
};

uint8_t glider[3][3] = {
	{0, 1, 0},
	{0, 0, 1},
	{1, 1, 1}
};

uint8_t segler[4][5] = {
	{0, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{0, 0, 0, 0, 1},
	{1, 0, 0, 1, 0}
};

uint8_t buffer[7][3] = {
	{1, 1, 1},
	{1, 0, 1},
	{1, 0, 1},
	{0, 0, 0},
	{1, 0, 1},
	{1, 0, 1},
	{1, 1, 1}
};

/* initialize world with zero (dead cells) */
void clean_world(uint8_t ** world, uint8_t width, uint8_t height) {
	int a;
	for (a = 0; a < width; a++) {
		memset(world[a], 0, height * sizeof(uint8_t));
	}
}

/* allocate memory for world */
uint8_t ** create_world(uint8_t width, uint8_t height) {
	uint8_t ** world = malloc(width * sizeof(uint8_t *));
	int a;
	for (a = 0; a < width; a++) {
		world[a] = malloc(height * sizeof(uint8_t));
	}

	clean_world(world, width, height);
	return world;
}

/* insert pattern at (x|y) into world */
void inhabit_world(struct pattern pattern, uint8_t x, uint8_t y, uint8_t ** world) {
	uint8_t a, b;

	for (a = 0; a < pattern.height; a++) {
		for (b = 0; b < pattern.width; b++) {
			world[x+b][y+a] = pattern.data[(a*pattern.width)+b];
		}
	}
}

/* calc alive cells */
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
		int c = a;
		if (a < 0) c += width;
		if (a >= width) c -= width;

		for (b = y-1; b <= y+1; b++) {
			int d = b;
			if (a == x && b == y) continue;
			if (b < 0) d += height;
			if (b >= height) d -= height;

			neighbours += (world[c][d] > 0) ? 1 : 0;
		}
	}

	return neighbours; /* 0 <= neighbours <= 8 */
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
			return 1; /* kept alive */
		}
	}
	else if (neighbours == 3) {
		return 1; /* born */
	}
	else {
		return 0; /* still dead */
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

/* print world with colors and count of neighbours */
void print_world(uint8_t ** world, uint8_t width, uint8_t height) {
	uint8_t x, y;
	move(0, 0); /* reset cursor */

	/* cells */
	for (y = 0; y < height; y++) {
		for (x = 0; x < width; x++) {
			uint8_t neighbours = calc_cell_neighbours(x, y, world, width, height);

			if (neighbours > 1) attron(COLOR_PAIR(neighbours));
			addch((world[x][y]) ? '0' + neighbours : ' ');
			if (neighbours > 1) attroff(COLOR_PAIR(neighbours));
		}
	}
}

void print_cursor(uint8_t ** world, struct cursor cur) {
	uint8_t color = (world[cur.x][cur.y]) ? 7 : 6;

	move(cur.y, cur.x);
	addch(CURSOR_CHAR | A_BLINK | A_BOLD | A_STANDOUT | COLOR_PAIR(color));
}

/* set up ncurses screen */
WINDOW * init_screen() {
	WINDOW * win = initscr();
	noecho();
	timeout(0);
	keypad(win, 1);
	mousemask(BUTTON1_CLICKED, NULL);
	mouseinterval(200);
	curs_set(0);

	start_color();
	init_color(COLOR_CYAN, 500, 1000, 0);  /* redefine as orange */

	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	init_pair(6, COLOR_BLUE, COLOR_BLACK);
	init_pair(7, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(8, COLOR_RED, COLOR_BLACK);

	return win;
}

int main(int argc, char * argv[]) {
	WINDOW * win = init_screen();
	MEVENT event;

	/* predefined patterns */
	struct pattern patterns[] = {
		{3, 3, (uint8_t *) start},
		{3, 3, (uint8_t *) glider},
		{5, 4, (uint8_t *) segler},
		{3, 7, (uint8_t *) buffer}
	};
	struct cursor cur = {0, 0};

	int generation = 0, input, framerate = 17;
	uint8_t width, height, paused = 0, a, b;
	uint8_t ** worlds[2], ** world;

	/* initialize world */
	getmaxyx(win, height, width);
	for (a = 0; a < 2; a++)
		worlds[a] = create_world(width, height); /* current generation */
	world = worlds[0];
	inhabit_world(patterns[3], width/2, height/2, worlds[0]);

	/* simulation loop */
	while(1) {
		/* calc next generation */
		if (!paused) {
			usleep(1 / (float) framerate * 1000000); /* sleep */
			calc_next_gen(world, worlds[++generation % 2], width, height);
			world = worlds[generation % 2]; /* new world */
		}

		/* handle events */
		switch (input = getch()) {
			case '+': /* increase framerate */
				framerate++;
				break;

			case '-': /* decrease framerate */
				if (framerate > 1) framerate--;
				break;

			case 'q': /* quit */
				endwin();
				exit(0);
				break;

			case 'p': /* pause */
				paused ^= 1;
				break;

			case 'c': /* clean world */
				clean_world(world, width, height);
				generation = 0;
				break;

			case '0': /* insert pattern */
			case '1':
			case '2':
			case '3':
				inhabit_world(patterns[input - '0'], cur.x, cur.y, world);
				break;

			case ' ': /* toggle cell at cursor position */
				world[cur.x][cur.y] = (world[cur.x][cur.y]) ? 0 : 1;
				break;

			case KEY_MOUSE: /* move cursor to mouse posititon */
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

		/* update screen */
		print_world(world, width, height);
		print_cursor(world, cur);

		attron(COLOR_PAIR(1));
		mvprintw(0, 0, "generation: %d\tcells: %d framerate: %d fps\twidth: %d\theight: %d cursor: (%d|%d)\n", generation, calc_cell_count(world, width, height), framerate, width, height, cur.x, cur.y);
		if (paused) mvprintw(0, width-6, "PAUSED");
		attroff(COLOR_PAIR(1));

		refresh();
	}

	/* householding */
	for (a = 0; a < 2; a++) {
		for (b = 0; b < width; b++) {
			free(worlds[a][b]);
		}
		free(worlds[a]);
	}

	endwin(); /* exit ncurses mode */

	return 0;
}
