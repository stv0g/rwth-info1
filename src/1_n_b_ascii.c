#include <stdio.h>

int main() {
	char letter = 'A';
	printf("Letter\tDec in ASCII-Table\n");

	do printf("%c\t\t\t%d\n", letter, letter);
	while (letter++ <= 'Z');

	return 0;
}
