#include <stdio.h>

char *str = "Hello World!\n";

int main () {
	int Laenge = 0;
	char * str_pointer = str;

	while (*str_pointer++ != '\0' ) {
		++Laenge;
	}

	printf("%d: %s", Laenge, str);

	return 0;
}
