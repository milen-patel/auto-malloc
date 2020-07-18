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

	/* Experimental */
	//MemoryItem *current = (MemoryItem *) Vec_ref(&objects, 0);
	//printf("Addy: %p\n", current);
	//printf("Val: %d\n", *((int *) current->memVal));
	//free(((int *) current->memVal));
	
	/* Iterate over each item in objects */
	for (int i = 0; i < Vec_length(&objects); i++) {
		/* Get the curent Vec item */
		MemoryItem *current = (MemoryItem *) Vec_ref(&objects, i);

		printf("numBytes: %lu\n", current->numBytes);
		printf("val: %d\n", *((int *) current->memVal));

		free((int *) current->memVal);
		//for (size_t j = 0; j < current->numBytes; j++) {
		//	char *currentByte = ((char *) current->memVal) + j;
		//	printf("J=%lu, PTR=%p \n", j, currentByte);
		//	free(currentByte);
		//}

	}

	/* Free all of our heap memory TODO */
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

int* new_int() {
	/* Make sure that we are already running */
	if (!isRunning) {
		printf("ERROR: Cannot request memory without calling am_start()!\n");
		return NULL;
	}

	/* Request heap memory */
	int *ptr = (int *) malloc(sizeof(int));

	/* Request Heap Memory for MemoryItem */
	MemoryItem stor = {
	sizeof(int),
	ptr
	};
	

	/* Set value to 0 */
	*ptr = 0;

	/* Add the value to internal list */
	Vec_set(&objects, Vec_length(&objects), &stor);

	/* Return the value to the user */
	return ptr;
}
