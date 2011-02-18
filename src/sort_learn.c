#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

/* global variables */
int n = 10;
int *data;

int is_sorted(int *data, int length) {
	int i;
	for (i = 1; i < length; i++) {
		if (data[i] < data[i-1]) {
			return FALSE;
		}
	}
	return TRUE;
}

void fill_random(int *data, int length) {
	srand(time(NULL));
	
	int i;
	for (i = 0; i < length; i++) {
		data[i] = rand() % 99 + 1;
	}
}

void print_data(int *data, int length) {
	int i;
	for (i = 0; i < length; i++) {
		printf("%d ", data[i]);
	}
	printf("\n");
}

void scan_data(int *data, int length) {
	int i;
	for (i = 0; i < length; i++) {
		scanf("%d", data + i);
	}
}

void challenge_data(int *data, int length) {
	int input[length];
	scan_data(input, length);
	
	if (memcmp(data, input, length)) {
		printf("game over!\n");
		print_data(data, length);
		exit(-1);
	}
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selection_sort(int *l, int *r) {
	int *p;
	for (p = l; p <= r; p++) {
		int *q, *min = p;
		for (q = p+1; q <= r; q++) {
			if (*q < *min) {
				min = q;
			}
		}
		
		if (p != min) {
			swap(p, min);
			challenge_data(data, n);
		}
	}
}

void insertion_sort(int *l, int *r) {
	int *p;
	for (p = l+1; p <= r; p++) {
		int *q, v = *p;
		for (q = p-1; q >= l; q--) {
			if (v < *q) {
				*(q+1) = *q;
				challenge_data(data, n);
			}
			else {
				break;
			}
		}
		*(q+1) = v;
		challenge_data(data, n);
	}
}

void bubble_sort(int *l, int *r) {
	int *p;
	for (p = l; p <= r; p++) {
		int *q;
		for (q = r; q > p; q--) {
			if (*(q-1) > *q) {
				swap(q-1, q);
				challenge_data(data, n);
			}
		}
	}
}

void quick_sort(int *l, int *r) {
	int *i = l, *j = r-1, *k = r;
	
	if (l >= r) return; /* Abbruchkriterium für Rekursion */

	while (1) {
		while (*i < *k && i < r) i++;
		while (*j > *k && j > l) j--;

		if (i >= j) /* Aneinander vorbei gelaufen? */
			break;
		else {
			swap(i, j);
			challenge_data(data, n);
		}
	}

	swap(k, i);
	challenge_data(data, n);
	
	/* Rekursion */
	quick_sort(l, i-1);
	quick_sort(i+1, r);
}

void heap_sink(int *l, int *r, int *node) {
	while (1) {
		int * son = l+2*(node-l+1)-1; /* der erste Sohn */

		if (son+1 > r) { /* keine Söhne */
			break;
		}
		else if (son+1 <= r && *(son+1) < *son) { /* zwei Söhne */
			son++;
		}
		
		if (*son < *node) { /* Vertauschen notwendig? */
			swap(son, node);
			challenge_data(data, n);
			node = son;
		}
		else {
			break;
		}
	}
}

void heap_sort(int *l, int *r) {
	int *p;
	
	/* create heap */
	for (p = l-1+(r-l+1)/2; p >= l; p--) {
		heap_sink(l, r, p);
	}

	/* sort */
	for (p = r; p > l; p--) {
		swap(l, p);
		challenge_data(data, n);
		printf("sinking: %d\n", *l);
		heap_sink(l, p-1, l);
	}
}

struct algorithm_t {
	char * name;
	void (*function)(int*, int*);
} algorithms[] = {
	{"selection sort", selection_sort},
	{"insertion sort", insertion_sort},
	{"bubble sort", bubble_sort},
	{"quick sort", quick_sort},
	{"heap sort", heap_sort}
};

int main(int argc, char * argv[]) {
	if (argc == 1 || argc > 3) {
		printf("choose the algorithm:\n");
		int i;
		for (i = 0; i < 5; i++) {
			printf("%d: %s\n", i+1, algorithms[i].name);
		}
		printf("\nrun as: %s #algno #length\n", argv[0]);
		exit(0);
	}
	
	struct algorithm_t alg = algorithms[0];
	
	if (argc > 1) {
		alg = algorithms[atoi(argv[1]) - 1];
	}
	
	if (argc > 2) {
		n = atoi(argv[2]);
	}

	printf("starting with %s and %d numbers\n", alg.name, n);
	
	/* allocate memory for numbers */
	data = (int *) malloc(n * sizeof(int));
	
	/* initialize numbers by random */
	fill_random(data, n);
	print_data(data, n);
	
	time_t start = time(NULL);
	alg.function(data, data+n-1);
	time_t end = time(NULL);
	
	printf("you won!\n");
	printf("sorting completed in %d seconds\n", (int) (end - start));
	return 0;
}


