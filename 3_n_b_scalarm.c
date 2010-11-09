#include <stdio.h>
#include <math.h>

#define DIMENSION 2

int main() {
	float matrix[DIMENSION][DIMENSION] = {
		{2.1, 3.0},
		{4.2, 3.5}
	};

	float scalar;
	int i, j;

	printf("Matrix before operation:\n");
	for (i = 0; i < DIMENSION; i++) {
		for (j = 0; j < DIMENSION; j++) {
			printf("%.3f\t", matrix[i][j]);
		}
		printf("\n");
	}

	printf("Please enter a scalar to multiply with: ");
	scanf("%f", &scalar);

	printf("Matrix after operation:\n");
	for (i = 0; i < DIMENSION; i++) {
		for (j = 0; j < DIMENSION; j++) {
			matrix[i][j] *= scalar;
			printf("%.3f\t", matrix[i][j]);
		}
		printf("\n");
	}

	return 0;
}
