#include <stdio.h>

#define ROWS 4
#define COLS ROWS

int main() {
	int matrix[ROWS][COLS] = {
		{1,  2,  3,  4},
		{5,  6,  7,  8},
		{9,  10, 11, 12},
		{13, 14, 15, 16}
	};

	int x, y;

	/* transpose */
	for (x = 0; x < ROWS; x++) {
		for (y = 0; y < x; y++) {
			int temp = matrix[x][y];
			matrix[x][y] = matrix[y][x];
			matrix[y][x] = temp;
		}
	}

	/* output */
	for (x = 0; x < ROWS; x++) {
		for (y = 0; y < COLS; y++) {
			printf("%d\t", matrix[x][y]);
		}
		printf("\n");
	}

	return 0;
}
