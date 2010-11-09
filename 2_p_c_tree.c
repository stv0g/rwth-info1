#include <stdio.h>

int main() {
	int level;
	for (level = 1; level < 7; level++) {
		int column;
		for (column = 1; column <= level; column++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}
