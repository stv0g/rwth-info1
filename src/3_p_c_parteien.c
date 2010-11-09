#include <stdio.h>

#define MAX_SEATS 200
#define THRESHOLD 5

typedef struct {
	char * name;
	float percentage;
	int seats;
} party;

int main() {
	party parties[] = {
		{"MFG", 40.3},
		{"Mitte", 55.0},
		{"EBS", 4.7}
	};

	int i;
	const int party_count = sizeof parties / sizeof (party);
	float significant_percentage = 0;

	for (i = 0; i < party_count; i++) {
		if (parties[i].percentage >= THRESHOLD) {
			significant_percentage += parties[i].percentage;
		}
	}

	for (i = 0; i < party_count; i++) {
		parties[i].seats = parties[i].percentage >= THRESHOLD ? MAX_SEATS * (parties[i].percentage / significant_percentage) : 0;
		printf("%s\t%.1f%%\t(%d Sitze)\n", parties[i].name, parties[i].percentage, parties[i].seats);
	}

	return 0;

}
