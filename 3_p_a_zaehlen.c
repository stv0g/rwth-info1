#include <stdio.h>

#define NEEDLE 'e'

int main() {
	int counter = 0;
	char character;

	printf("Please enter a message: ");
	while ((character = getchar()) != '\n') {
		if (character == NEEDLE) counter++;
	}

	printf("Found '%c' %d times\n", NEEDLE, counter);

	return 0;
}
