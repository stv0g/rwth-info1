#include <stdio.h>

int main() {
	/* table header */
	printf("a\tb\t!a\ta || b\ta && b\ta^b\n");
	printf("--------------------------------------------\n");

	int a, b;
	for (a= 0; a < 2; a++) {
		for (b = 0; b < 2; b++) {
			printf("%d\t%d\t%d\t%d\t%d\t%d\n", a, b, !a, a || b, a && b, a^b);
		}
	}

	return 0;
}
