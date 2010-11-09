#include <stdio.h>

#define DIMENSION 4

int main() {
	int matrix[DIMENSION][DIMENSION] = {
		{1,  2,  3,  4},
		{5,  6,  7,  8},
		{9,  10, 11, 12},
		{13, 14, 15, 16}
	};

	int temp, x, y;

	for (x = 0; x < DIMENSION; x++) {
		for (y = 0; y < x; y++) {
			temp = matrix[x][y];
			matrix[x][y] = matrix[y][x];
			matrix[y][x] = temp;
		}
	}

	for (x = 0; x < DIMENSION; x++) {
		for (y = 0; y < DIMENSION; y++) {
			printf("%d\t", matrix[x][y]);
		}
		printf("\n");
	}

	return 0;
}
