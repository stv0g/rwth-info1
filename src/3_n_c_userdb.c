#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 10
#define BUFFER_SIZE 256

typedef struct {
	char active;
	char * name;
	char * password;
} user;

int main() {
	user users[MAX_ACCOUNTS];
	char input_buffer[BUFFER_SIZE];
	int count, offset;

	for (offset = 0, count = 0; offset < MAX_ACCOUNTS; offset++, count++) {
		printf("Should this user be activated? (0/1/-1): ");  /* -1 for break input */
		fgets(input_buffer, BUFFER_SIZE, stdin);
		users[offset].active = atoi(input_buffer);
		if (users[offset].active == -1) {
			break;
		}

		printf("Please enter a username: ");
		fgets(input_buffer, BUFFER_SIZE, stdin);
		users[offset].name = malloc(strlen(input_buffer));
		strncpy(users[offset].name, input_buffer, strlen(input_buffer)-1);

		printf("Please enter a password: ");
		fgets(input_buffer, BUFFER_SIZE, stdin);
		users[offset].password = malloc(strlen(input_buffer));
		strncpy(users[offset].password, input_buffer, strlen(input_buffer)-1);
	}

	if (count > 0) {
		/* table header */
		printf("No.\tName\t\t\tPassword\t\tActive?\n");

		for (offset = 0; offset < count; offset++) {
			printf("%d\t%-24s%-24s%s\n", offset+1, users[offset].name, users[offset].password, users[offset].active ? "yes" : "no");
		}
		return 0;
	}
	else {
		return -1;
	}
}
