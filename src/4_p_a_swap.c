#include <stdio.h>

void swap(int * a, int * b);	/* function declaration */

int main() {
	int a = 4, b = 14;

	swap(&a, &b);

	printf("a = %d\nb = %d\n", a, b);

	return 0;
}

void swap(int * a, int * b) {	/* funtion implementation */
	int temp = *a;
	*a = *b;
	*b = temp;
}
