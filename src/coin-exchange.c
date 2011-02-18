#include <stdio.h>
#include <math.h>
#include <string.h>

const int types[] = {1, 5, 10, 20, 50, 100, 200}; /* in euro cents; types[0] = 1 */

int calc_total(int * quantity, int n) {
	int i, total = 0;
	for (i = 0; i < n; i++) total += quantity[i] * types[i];
	return total;
}

int exchange(int cents, int n, int * quantity) {
	int i;
	int best[3] = {	/* initialized with worstcase */
		0,	/* coin type */
		cents,	/* coin quantity */
		cents	/* total coin quantity */
	};


	for (i = n; i >= 0; i--) {
		int coins = floor(cents / types[i]);
		int rest = cents - coins * types[i];
		int total_coins = exchange(rest, n-1, quantity);
		if (total_coins < best[2]) {
			best[0] = i;
			best[1] = coins;
			best[2] = total_coins;
		}
	}

	quantity[best[0]] = best[1];

	/* debug START */
	printf("[%d] choosen %d of %d (total %d)\n", n, best[1], best[0], best[2]);
	for (i = 0; i < 7; i++) printf("%d ", quantity[i]);
	printf("\n");
	/* debug END */

	return best[2];
}

int main() {
	float euros;
	int cents, i, n = sizeof(types) / sizeof(int);
	int quantity[n];

	memset(quantity, 0, sizeof(quantity));

	printf("What do you want to change?\nAmount (ex. 22.50): ");
	scanf("%f", &euros);
	cents = (int) (euros * 100);

	if (cents) {
		int coins = exchange(cents, n-1, quantity);

		printf("You will get %d coins:\n", coins);
		for (i = 0; i < n; i++) {
			if (quantity[i] > 0)
				printf(
					"\t%d %d %s %s\n",
					quantity[i],
					(types[i] >= 100) ? types[i] / 100 : types[i],
					(types[i] < 100) ? "cent" : "euro",
					(quantity[i] > 1) ? "coins" : "coin"
				);
		}
		printf("Total: %f\n", euros);
	}
	else {
		fprintf(stderr, "Please enter a valid amount of money!\n");
		return -1;
	}

	return 0;
}
