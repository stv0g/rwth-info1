#include <stdio.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>

const int earth_radius = 6380;

struct Entry {
	int locid;		/* Location ID (Primärschlüssel) */
	char *ags;		/* Amtlicher Gemeindeschlüssel */
	char *ascii;		/* Sortiername */
	char *name;		/* Name */
	double lat;		/* Breitengrad (latitude) */
	double lon;		/* Längengrad (longitude) */
	char *amt;		/* Verwaltungszusammenschluss  */
	char *plz;		/* Postleitzahl */
	char *vorwahl;		/* Telefonvorwahl */
	int einwohner;		/* Einwohnerzahl */
	float flaeche;		/* Fläche */
	char *kz;		/* KFZ-Kennzeichen */
	char *typ;		/* Typ (dem Eintrag nach lokal-/spezialisiert) */
	int level;		/* Ebene */
	int of;			/* Teil von */
	int invalid;		/* Markierung als ungültig */
};

/* Implementation of double linked list */
struct Node {
	struct Entry *data;
	struct Node *previous;
	struct Node *next;
};

struct List {
	struct Node *start;
	struct Node *end;
};

struct List list_init() {
	struct List list = {NULL, NULL};
	return list;
}

char list_isempty(struct List *list) {
	return list->end == NULL && list->start == NULL;
}

void list_append(struct List *list, struct Entry *data) {
	struct Node *node = malloc(sizeof(struct Node));

	node->data = data;
	node->next = NULL;

	if (list_isempty(list)) {
		node->previous = NULL;
		list->start = node;
		list->end = node;
	}
	else {
		node->previous = list->end;
		list->end->next = node;
		list->end = node;
	}
}

void list_swap(struct Node *n1, struct Node *n2) {
	struct Entry *temp = n1->data;

	n1->data = n2->data;
	n2->data = temp;
}

/* returns the distance between two entries in kilemeters */
float calc_distance(struct Entry *e1, struct Entry *e2) {
	return acos(sin(e2->lat) * sin(e1->lat) + cos(e2->lat) * cos(e1->lat) * cos(e2->lon - e1->lon)) * earth_radius;
}

typedef int(*cmp_func_t)(struct Entry *, struct Entry *);

int cmp_name(struct Entry *e1, struct Entry *e2) {
	return strcmp(e1->ascii, e2->ascii);
}

int cmp_area(struct Entry *e1, struct Entry *e2) {
	return e2->flaeche - e1->flaeche;
}

int cmp_residents(struct Entry *e1, struct Entry *e2) {
	return e2->einwohner - e1->einwohner;
}

/* compares distance realtive to e3 */
int cmp_distance(struct Entry *e1, struct Entry *e2, struct Entry *e3) {
	return calc_distance(e2, e3) - calc_distance(e1, e3);
}

/* Linear search on list */
struct Entry * lsearch(char *needle, struct Node *start, struct Node *end) {
	struct Node *n = start;

	while (n != end) {
		if (strcmp(n->data->ascii, needle) == 0)
			return n->data;
		else
			n = n->next;
	}

	return NULL; /* not found */
}

/* custom strtok() alike implementation */
char * strtok_c(char *string, char delim) {
	static char *origin;
	char *start;

	if (string != NULL)
		origin = string;

	if (*origin == '\0')
		return NULL;
	else {
		start = origin;
		while (*origin != delim && *origin != '\0')
			origin++;

		if (*origin != 0)
			*origin++ = '\0';

		return start;
	}
}

/* helper to allocate memory and copy string */
char * strallocpy(char *string) {
	if (string) {
		char *parsed = malloc(strlen(string) * sizeof(char) + 1);
		return strcpy(parsed, string);
	}
	return string;
}

struct Entry * parse_row(char row[1024]) {
	struct Entry *entry = malloc(sizeof(struct Entry));
	char *col = strtok_c(row, '\t'), col_num = 0;

	do {
		switch (col_num++) {
			case 0: entry->locid	= atoi(col); break;
			case 1: entry->ags	= strallocpy(col); break;
			case 2: entry->ascii	= strallocpy(col); break;
			case 3: entry->name	= strallocpy(col); break;
			case 4: entry->lat	= atof(col); break;
			case 5: entry->lon	= atof(col); break;
			case 6: entry->amt	= strallocpy(col); break;
			case 7: entry->plz	= strallocpy(col); break;
			case 8: entry->vorwahl	= strallocpy(col); break;
			case 9: entry->einwohner	= atoi(col); break;
			case 10: entry->flaeche	= atof(col); break;
			case 11: entry->kz	= strallocpy(col); break;
			case 12: entry->typ	= strallocpy(col); break;
			case 13: entry->level	= atoi(col); break;
			case 14: entry->of	= atoi(col); break;
			case 15: entry->invalid	= atoi(col); break;
		}
	} while ((col = strtok_c(NULL, '\t')));

	return entry;
}

struct List parse_db(char *path) {
	struct List entries = list_init();
	char row[1024];
	FILE *db = fopen(path, "r");

	if (db == NULL) {
		perror ("Error opening database");
		exit(-1);
	}

	while(!feof(db)) {
		if (fgets(row, 1024, db) && *row != '#') { /* ignore comments */
			list_append(&entries, parse_row(row));
		}
	}

	fclose(db);
	return entries;
}

void quicksort(struct Node *start, struct Node *end, int (*cmp)(struct Entry *e1, struct Entry *e2)) {

}

void print_entry(struct Entry *e) {
	printf("%7d: %-40s\t%-15d\t%.2f\t%s\t(%f|%f)\n", e->locid, e->name, e->einwohner, e->flaeche, e->plz, e->lat, e->lon);
}

int main(int argc, char *argv[]) {
	char needle[20];
	struct Entry *result;

	int action, i = 0;	

	if (argc < 2) {
		fprintf(stderr, "Path to database omitted!\n");
		exit(-1);
	}

	struct List entries = parse_db(argv[1]); /* parse database */

	/* ask for criterium */
	printf("What do you want to do?:\n1) sort by name\n2) sort by residents\n3) sort by area\n4) sort by distance\n5) search for entry\nYour choice: ");
	scanf("%d", &action);

	switch(action) {
		case 1:
			quicksort(entries.start, entries.end, cmp_name);
			break;
		case 2:
			quicksort(entries.start, entries.end, cmp_residents);
			break;
		case 3:
			quicksort(entries.start, entries.end, cmp_area);
			break;
		/*case 4:
			quicksort(entries.start, entries.end, cmp_distance);
			break;*/
		case 5:
			printf("what are you searching: ");
			scanf("%s", needle);
			result = lsearch(needle, entries.start, entries.end);
			print_entry(result);
			
		default:
			fprintf(stderr, "Invalid sort criteria!\n");
	}

	/* show result */
	if (action != 5) {
		struct Node *node;
		for (node = entries.start; node != entries.end && i++ < 100; node = node->next) {
			print_entry(node->data);
		}
	}

	return 0;
}
