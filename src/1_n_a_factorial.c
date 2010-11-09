#include <stdio.h>
#define N 10

int main() {
	int i, solution = 1;

	for (i = 1; i <= N; i++) { 
		solution *= i;
		printf("The factorial of %d is:\t%d\n", i, solution);
	}

	return 0;
}

