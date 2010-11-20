#include <stdio.h>

#define NOT_FOUND -1

void swap(int * a, int * b);
void print_array(int array[], size_t start, size_t end);
void selection_sort(int array[], size_t start, size_t end);
int binary_search(int array[], int needle, size_t start, size_t end);


int main() {
	/* int data[] = {2, 5, 9, 18, 23, 34, 36, 99}; */
	int data[] = {243, 12, 12, 74, 346, 32, 93, 1, 0, 26, 236, 2, 12323};
	int needle, found = NOT_FOUND;
	size_t size = sizeof(data) / sizeof(int);

	printf("What are your looking for?: ");
	scanf("%d", &needle);

	printf("Data before sorting: ");
	print_array(data, 0, size);

	selection_sort(data, 0, size);

	printf("Data after sorting: ");
	print_array(data, 0, size);

	found = binary_search(data, needle, 0, size);

	if (found != NOT_FOUND) {
		printf("%d is at the %dth position\n", needle, found);
		return 0;
	}
	else {
		printf("%d was not found!\n", needle);
		return -1;
	}
}

void print_array(int array[], size_t start, size_t end) {
	int index;
	for (index = start; index < end; index++) {
		printf("%d,", array[index]);
	}
	printf("\n"); 
}


/* simple selection sort algorithm for an int array */
void selection_sort(int array[], size_t start, size_t end) {
	int min_index, progress, index;

	for (progress = start; progress < end; progress++) {
		min_index = progress;
		for (index = progress; index < end; index++) {
			if (array[index] < array[min_index]) {
				min_index = index;
			}
		}
		swap(&array[progress], &array[min_index]);
	}
}

/* do a binary search on a previously sorted array */
int binary_search(int array[], int needle, size_t start, size_t end) {
	size_t middle;

	while (end >= start) {
		middle = (end + start) / 2;

		if (array[middle] == needle) {
			return middle;
		}

		if (needle < array[middle]) {
			end = middle - 1;
		}
		else {
			start = middle + 1;
		}
	}

	return NOT_FOUND;
}

/* swap two int values referenced by pointers */
void swap(int * a, int * b) {
	int temp = *a;

	*a = *b;
	*b = temp;
}

