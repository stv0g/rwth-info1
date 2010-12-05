#include<stdio.h>

#define COUNT 7

struct partei {
	char name[20];
	int stimmen;
} parteien[COUNT] = {
	{"CDU", 30},
	{"SPD", 23},
	{"Gruene", 13},
	{"Piraten", 100},
	{"Partei", 2},
	{"Linke", 7},
	{"FDP", 22}
};

void vertausche(struct partei * z1, struct partei * z2) {
	struct partei temp;
	temp = *z1;
	*z1 = *z2;
	*z2 = temp;
}

/* vgl. strcmp() aus strings.h */
int vergleicheString(char *linkerstring, char *rechterstring) {
	while (*linkerstring == *rechterstring && *linkerstring) {
		linkerstring++;
		rechterstring++;
	}

	if (*linkerstring < *rechterstring)
		return -1;
	if (*linkerstring > *rechterstring)
		return 1;
	else return 0;
}

/* vgl. Namen zweier Parteien */
int vergleicheNamen(struct partei * p1, struct partei * p2) {
	return vergleicheString(p1->name, p2->name);
}

/* vgl. Stimmen zweier Parteien */
int vergleicheStimmen(struct partei * p1, struct partei * p2) {
	return p2->stimmen - p1->stimmen;
}

/* Quicksort Implementation */
void quicksort(struct partei *start, struct partei *ende, int (*cmp)(struct partei *, struct partei *)) {
	struct partei *i = start, *j = ende - 1, *trenn = ende;

	if (start >= ende) return; /* Abbruchkriterium für Rekursion */

	while (1) {
		while ((*cmp)(i, trenn) <= 0 && i < ende) i++;
		while ((*cmp)(j, trenn) >= 0 && j >= start) j--;

		if (i >= j)
			break;
		else
			vertausche(i, j);
	}

	vertausche(trenn, i);
	quicksort(start, i-1, cmp);
	quicksort(i+1, ende, cmp);
}

int main(int argc, char * argv[]) {
	int i;

	for (i = 0; i < COUNT; i++) {
                printf("%d:\t%s\n", i+1, parteien[i].name);
        }

	printf("\nSortiere nun mit Quicksort nach Namen\n\n");
	quicksort(parteien, parteien + COUNT - 1, vergleicheNamen);

	for (i = 0; i < COUNT; i++) {
		printf("%d:\t%s\n", i+1, parteien[i].name);
	}

	printf("\nSortiere nun mit Quicksort nach Stimmen\n\n");
	quicksort(parteien, parteien + COUNT - 1, vergleicheStimmen);

	for (i = 0; i < COUNT; i++) {
		printf("%d:\t%s:\t%d\n", i+1, parteien[i].name, parteien[i].stimmen);
	}


	return 0;
}
