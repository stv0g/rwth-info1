#include <stdio.h>

#define DELTA 1
#define MAX 10

int main() {
	int umfang, flaeche, a = 0;
	do {
		umfang = 4*a;
		flaeche = a*a;
		printf("Seitenlaenge = %d cm \t=> Fläche = %d cm^2 \tund Umfang = %d cm\n", a, flaeche, umfang);
		a = a + DELTA;
	} while (a <= MAX);

	return 0;
}
