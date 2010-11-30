#include <stdio.h>
#include <stdlib.h>

/* declarations */
int sum(int n);
int sum2(int n);
int fib(int n);

int main() {
	int n;

	printf("Please enter n: ");
	scanf("%d", &n);
	printf("fib(%d) = %d\nsum(%d) = %d\n", n, fib(n), n, sum2(n));

	return 0;
}

int sum(int n) {
	int i, sum = 0;

	for (i = 1; i <= n; i++) {
		sum += i;
	}

	return sum;
}

int sum2(int n) {
	return (n > 1) ? sum2(n-1) + n : 1;
}

int fib(int n) {
	return (n < 2) ? n : fib(n-1) + fib(n-2);
}

