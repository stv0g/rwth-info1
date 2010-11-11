#include <stdio.h>

int i = 0;

void swap (int * x, int * y) {
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

int f() {
	i++;
	return i;
}

int main () {
	int feld[4] = {4, 3, 2, 1};
	int zahl1 = 5, zahl2 = 3;

	/* 2. Aufgabenteil */
	printf("vor swap: zahl1=%d, zahl2=%d\n", zahl1, zahl2);
	swap(&zahl1, &zahl2);
	printf("nach swap: zahl1=%d, zahl2=%d\n", zahl1, zahl2);

	/* 3. Aufgabenteil */
	printf ("feld-Inhalt vor swap: {%d, %d, %d, %d}\n", feld[0], feld[1], feld[2], feld[3]);
	swap (&i, &feld[f()]);
	printf ("feld-Inhalt nach swap: {%d, %d, %d, %d}\n", feld[0], feld[1], feld[2], feld[3]);

	return 0;
}

