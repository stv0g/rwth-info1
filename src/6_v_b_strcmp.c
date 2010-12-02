#include <stdio.h>

char * cmp[] = {"before", "equal", "behind"};

int strcmp(char * s1, char * s2) {

	while (*s1 == *s2 && *s1) {
		s1++;
		s2++;
	}

	if (*s1 < *s2)
		return -1;
	if (*s1 > *s2)
		return 1;
	else
		return 0;
}

int main(int argc, char * argv[]) {

	char * s1 = "Aachen";
	char * s2 = "Aach";
	char * s3 = "Berlin";

	printf("%s is %s %s\n", s1, cmp[strcmp(s1, s2)+1], s2);
	printf("%s is %s %s\n", s1, cmp[strcmp(s1, s3)+1], s3);

	return 0;
}
