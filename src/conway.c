#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

/* configuration */
#define CELL_CHAR '#'
#define CURSOR_CHAR 'X'
#define WIDTH 80
#define HEIGHT 24
#define ESC 27
#define FRAME_RATE 5

void clear_screen() {
	printf("%c[2J", ESC);
}

void set_cursor(int row, int col) {
	printf("%c[%d;%dH", ESC, row, col);
}

void clean_world(uint8_t world[WIDTH][HEIGHT]) {
	size_t a, b;

	for (a = 0; a < WIDTH; a++) {
		for (b = 0; b < HEIGHT; b++) {
			world[a][b] = 0;
		}
	}
}

void inhabit_world(uint8_t pattern[3][3], size_t x, size_t y, uint8_t world[WIDTH][HEIGHT]) {
	size_t a, b;

	for (a = 0; a < 3; a++) {
		for (b = 0; b < 3; b++) {
			world[x+b][y+a] = pattern[a][b];
		}
	}
}

uint8_t calc_cell_neighbours(size_t x, size_t y, uint8_t world[WIDTH][HEIGHT]) {
	uint8_t neighbours = 0;
	int8_t a, b;

	for (a = x-1; a <= x+1; a++) {
		for (b = y-1; b <= y+1; b++) {
			if (a >= 0 && b >= 0 && a != x && b != y && world[a][b] > 0) {
				neighbours++;
			}
		}
	}

	return neighbours;
}

uint8_t calc_next_cell_gen(size_t x, size_t y, uint8_t world[WIDTH][HEIGHT]) {
	uint8_t neighbours = calc_cell_neighbours(x, y, world);

	if (neighbours < 2) {
		return 0;
	}
	else if (neighbours > 3) {
		return 0;
	}
	else if (neighbours == 2 || neighbours == 3) {
		return 1;
	}
	else {
		return -1;
	}
}

void calc_next_gen(uint8_t world[WIDTH][HEIGHT]) {
	uint8_t next_gen[WIDTH][HEIGHT];
	size_t x, y;

	clean_world(next_gen);

	for (x = 0; x < WIDTH; x++) {
		for (y = 0; y < HEIGHT; y++) {
			next_gen[x][y] = calc_next_cell_gen(x, y, world);
		}
	}

	memcpy(world, next_gen, WIDTH*HEIGHT);
}

void print_world(uint8_t world[WIDTH][HEIGHT]) {
	size_t x, y;

	/* reset cursor */
	set_cursor(0, 0);

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			/*printf("%c", (world[x][y]) ? CELL_CHAR : ' ');*/
			printf("%d,", (world[x][y] != 0) ? (int) world[x][y] : ' ');
		}
		printf("\n");  /* new line */
	}

	for (y = 0; y < HEIGHT; y++) {
		printf("|");
		for (x = 0; x < WIDTH; x++) {
			printf("%c", (world[x][y]) ? CELL_CHAR : ' ');
		}
		printf("|\n");  /* new line */
	}
}

/* start pattern */
uint8_t glider[3][3] =  {
	{0, 1, 0},
	{0, 0, 1},
	{1, 1, 1}
};

int main(int argc, char * argv[]) {
	uint8_t world[WIDTH][HEIGHT];
	int counter = 0;

	clean_world(world);  /* initialize world */
	inhabit_world(glider, WIDTH/2, HEIGHT/2, world);  /* inhabit world */
	clear_screen();
print_world(world);

	/* simulation loop */
	while(0) {
		calc_next_gen(world);
		print_world(world);
		usleep((float) 1 / FRAME_RATE * 1000000); /* sleep */
		printf("frame: %d\n", counter++);
	}

	return 0;
}
