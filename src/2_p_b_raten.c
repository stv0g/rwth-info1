#include <stdio.h>

#define MAX 3
#define FIND 'z'

int main() {
	int anzahl;
	char versuch;

	for(anzahl=1; anzahl <= 3; anzahl++) {
		printf("Enter letter:\t");
		scanf(" %c", &versuch); 

		if (versuch == FIND) {
			printf("Super!\n");
			return 0;
		}
		else {
			printf("Wrong! Next try!\n");
		}
	}
	printf("You missed all your chances!\n");

	return -1;
}


