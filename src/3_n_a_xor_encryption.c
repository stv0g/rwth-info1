#include <stdio.h>#include <string.h>#define MAX_LENGTH 31 /*  30 characters + '\0' termination */#define SALT 15int main() {	char input[MAX_LENGTH];	int offset = 0;	char character;	/* prompt for input */	printf("Please enter message: ");	while (offset + 1 < MAX_LENGTH && (character = getchar()) != '\n') {		input[offset++] = character;	}	input[offset] = '\0';	/* encrypt message */	for (offset = 0; offset < strlen(input); offset++) {		input[offset] ^= SALT;	}	printf("Encrypted message: %s\n", input);	/* decrypt message */	for (offset = 0; offset < strlen(input); offset++) {		input[offset] ^= SALT;	}	printf("Decrypted message: %s\n", input);	return 0;}