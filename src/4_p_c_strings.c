#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 81 /* 80 characters + '\0' termination */

int main () {
	int i;
	char str1[MAX_LENGTH]; /* Eingabestring */
	char str2[MAX_LENGTH]; /* Ausgabestring */
	char *p1, *p2;

	printf("Bitte ein Wort eingeben: ");
	scanf(" %s", str1);

	/* soll nur eine Ausgabe erfolgen, geht dies auch ohne str2 und zwar wie folgt: */
	printf("So soll das Ergebnis aussehen: ");

	for (i = strlen(str1) - 1; i>=0; i--) {
		printf("%c", str1[i]);
	}

	/* nun mit Kopie in str2: */
	p1 = str1 + strlen(str1) -1; /* p1 zeigt auf das Ende von str1 */
	p2 = str2; /* p2 zeigt auf den Anfang von str2 */

	/* von hinten nach vorn wird str1 zeichenweise nach str2 kopiert */
	while (p1 >= str1) {
		*p2++ = *p1--;
	}
	*p2 = '\0'; /* str2 Sting-Endezeichen abschliessen */

	/* Ausgabe beider Strings */
	printf("\n%s <--> %s\n", str1, str2);

	return 0;
}

