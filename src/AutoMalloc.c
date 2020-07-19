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

int* new_int() {
	/* Call general memory allocation function */
	int *ptr = (int *) new_general(sizeof(int));

	/* Check if value is NULL */
	if (ptr == NULL) {
		printf("Failed to create new integer\n");
		return NULL;
	}

	/* Set value to 0 */
	*ptr = 0;

	/* Return the value to the user */
	return ptr;
}
