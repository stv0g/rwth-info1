#include <stdio.h>
#include <stdlib.h>

/* declarations */
int sum(int n);
int fib(int n);

int main() {
	int n;

	printf("Please enter n: ");
	scanf("%d", &n);
	printf("fib(%d) = %d\nsum(%d) = %d\n", n, fib(n), n, sum(n));

	return 0;
}

int sum(int n) {
	int i, sum = 0;

	for (i = 1; i <= n; i++) {
		sum += i;
	}

	return sum;
}

int fib(int n) {
	if (n >= 2) {
		return fib(n-1) + fib(n-1);
	}
	else if (n == 1) {
		return 1;
	}
	else if (n == 0) {
		return 0;
	}
	else {
		fprintf(stderr, "Invalid parameter: %d", n);
		exit(-1);
	}
}

