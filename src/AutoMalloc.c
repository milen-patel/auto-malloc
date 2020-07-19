#include "AutoMalloc.h"
#include "Vec.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static bool isRunning = false;
static Vec objects;

void am_start() {
	/* Check to see if the function has already been called */
	if (isRunning) {
		printf("ERROR: Cannot call am_start multiple times\n");
		return;
	}

	/* Change the value of our internal variable */
	isRunning = true;

	/* Create memory on the heap to store our lookup table */
	objects = Vec_value(1, sizeof(MemoryItem));
	
	/* Inform the user */
	printf("Started\n");
}

void am_close() {
	/* Make sure that we are already running */
	if (!isRunning) {
		printf("ERROR: Cannot close AutoMalloc before starting!\n");
		return;
	}

	/* Iterate over each item in objects */
	for (int i = 0; i < Vec_length(&objects); i++) {
		/* Get the curent Vec item */
		MemoryItem *current = (MemoryItem *) Vec_ref(&objects, i);

		if (sizeof(int) == sizeof(current->numBytes)) {
			free((int *) current->memVal);
		} else if (sizeof(char) == sizeof(current->numBytes)) {
			free((char *) current->memVal);
		} else if (sizeof(short) == sizeof(current->numBytes)) {
			free((short *) current->memVal);
		} else if (sizeof(long) == sizeof(current->numBytes)) {
			free((long *) current->memVal);
		} else if (sizeof(unsigned int) == sizeof(current->numBytes)) {
			free((unsigned int *) current->memVal);
		}
	}

	/* Free the actual Vec itself */
	Vec_drop(&objects);

	/* Inform the user */
	printf("Closed\n");
}

void am_status() {
	if (!isRunning) {
		printf("Not running\n");
		return;
	}

	printf("Running\n");
}

void *new_general(size_t byteCount) {
	/* Make sure that we are already running */
	if (!isRunning) {
		printf("ERROR: Cannot request memory without calling am_start()!\n");
		return NULL;
	}

	/* Request heap memory */
	void *ptr = malloc(byteCount);

	/* Request Heap Memory for MemoryItem */
	MemoryItem stor = {
		byteCount,
		ptr
	};

	/* Add the value to internal list */
	Vec_set(&objects, Vec_length(&objects), &stor);

	/* Return the value to the user */
	return ptr;
}

char *new_char(char startingValue) {
	/* Call general memory allocation function */
	char *ptr = (char *) new_general(sizeof(char));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new char\n");
		return NULL;
	}

	/* Set value to specified amount */
	*ptr = startingValue;

	/* Return the value to the user */
	return ptr;
}

unsigned char *new_unsigned_char(unsigned char startingValue) {
	/* Call general memory allocation function */
	unsigned char *ptr = (unsigned char *) new_general(sizeof(unsigned char));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new unsigned char\n");
		return NULL;
	}

	/* Set value to specified amount */
	*ptr = startingValue;

	/* Return the value to the user */
	return ptr;
}

signed char *new_signed_char(signed char startingValue) {
	/* Call general memory allocation function */
	signed char *ptr = (signed char *) new_general(sizeof(signed char));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new signed char\n");
		return NULL;
	}

	/* Set value to specified amount */
	*ptr = startingValue;

	/* Return the value to the user */
	return ptr;
}

int* new_int(int startingValue) {
	/* Call general memory allocation function */
	int *ptr = (int *) new_general(sizeof(int));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new integer\n");
		return NULL;
	}

	/* Set value to specified amount */
	*ptr = startingValue;

	/* Return the value to the user */
	return ptr;
}

unsigned int *new_unsigned_int(unsigned int startingValue) {
	/* Call general memory allocation function */
	unsigned int *ptr = (unsigned int *) new_general(sizeof(unsigned int));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new unsigned integer\n");
		return NULL;
	}

	/* Set value to specified amount */
	*ptr = startingValue;

	/* Return the value to the user */
	return ptr;
}

short* new_short(short startingValue) {
	/* Call general memory allocation function */
	short *ptr = (short *) new_general(sizeof(short));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new short\n");
		return NULL;
	}

	/* Set value to specified amount */
	*ptr = startingValue;

	/* Return the value to the user */
	return ptr;
}

unsigned short *new_unsigned_short(unsigned short startingValue) {
	/* Call general memory allocation function */
	unsigned short *ptr = (unsigned short *) new_general(sizeof(unsigned short));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new unsigned short\n");
		return NULL;
	}

	/* Set value to specified amount */
	*ptr = startingValue;

	/* Return the value to the user */
	return ptr;
}

long* new_long(long startingValue) {
	/* Call general memory allocation function */
	long *ptr = (long *) new_general(sizeof(long));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new long\n");
		return NULL;
	}

	/* Set value to specified amount */
	*ptr = startingValue;

	/* Return the value to the user */
	return ptr;
}

unsigned long *new_unsigned_long(unsigned long startingValue) {
	/* Call general memory allocation function */
	unsigned long *ptr = (unsigned long *) new_general(sizeof(unsigned long));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new unsigned long\n");
		return NULL;
	}

	/* Set value to specified amount */
	*ptr = startingValue;

	/* Return the value to the user */
	return ptr;
}
