#include <stdio.h>
#include <math.h>

#define MAX 10

int main() {
	int n = 1;
	printf("Liste der ersten %d Quadratzahlen:\n", MAX);

	while (n <= MAX) {
		printf("%d\n", (int) pow(n, 2));
		n += 1;
	}

	return 0;
}
