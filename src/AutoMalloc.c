#include "AutoMalloc.h"
#include "Internal_Array.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

static bool isRunning = false;
static Array objects;

void am_start() {
	/* Check to see if the function has already been called */
	if (isRunning) {
		printf("ERROR: Cannot call am_start multiple times\n");
		return;
	}

	/* Change the value of our internal variable */
	isRunning = true;

	/* Create memory on the heap to store our lookup table */
	objects = Array_value(1, sizeof(MemoryItem));
}

void am_close() {
	/* Make sure that we are already running */
	if (!isRunning) {
		printf("ERROR: Cannot close AutoMalloc before starting!\n");
		return;
	}

	/* Iterate over each item in objects */
	for (int i = 0; i < Array_length(&objects); i++) {
		/* Get the curent Array item */
		MemoryItem *current = (MemoryItem *) Array_ref(&objects, i);

		if (current->type == STANDARD) {
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
		} else if (current->type == STRING) {
			/* If we have a string then memVal is a pointer to an AutoMalloc_String */
			AutoMalloc_String *strAddy = (AutoMalloc_String *) current->memVal;

			/* First, free the string itself */
			AutoMalloc_String_drop(strAddy);

			/* Then free the heap memory that we used to store the string struct */
			free(strAddy);
		}
	}

	/* Free the actual Array itself */
	Array_drop(&objects);

	/* Inform the user */
	printf("Closed\n");
}

void am_status() {
	if (!isRunning) {
		printf("Not running\n");
		return;
	}

	printf("Running");

	/* If we have more than one active item, print a table to the screen */
	if (Array_length(&objects) > 0) {
		/* Print table starter and header */
		printf("\n#####################\n");
		printf("# Address   | # Bytes \n");

		/* Iterate over all of the active items */
		for (int i = 0; i < Array_length(&objects); i++) {
			/* Get the curent Array item */
			MemoryItem *current = (MemoryItem *) Array_ref(&objects, i);

			/* Add entry to the table */
			printf("# %p | %lu \n", current->memVal, current->numBytes);
		}
		
		/* Print ending line to table */
		printf("#####################\n");
	} else {
		/* If we dont have any active items, inform the user */
		printf(". No active variables\n");
	}
}

AutoMalloc_String *new_string(int width) {
	/* Make sure that we are already running */
	if (!isRunning) {
		printf("ERROR: Cannot request memory without calling am_start()!\n");
		return NULL;
	}

	/* Validate input */
	if (width < 0) {
		printf("ERROR: Cannot create a string of negative length!\n");
		return NULL;
	}

	/* Request heap memory */
	void *ptr = malloc(sizeof(AutoMalloc_String));

	/* Create representation for  MemoryItem */
	MemoryItem stor = {
		sizeof(AutoMalloc_String),
		ptr,
		STRING
	};

	/* Make the ptr point to a valid AutoMalloc_String */
	AutoMalloc_String *strPtr = (AutoMalloc_String *) ptr;
	*strPtr = AutoMalloc_String_value(width);

	/* Add the value to internal list */
	Array_set(&objects, Array_length(&objects), &stor);

	/* Return the value to the user */
	return strPtr;
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
		ptr,
		STANDARD
	};

	/* Add the value to internal list */
	Array_set(&objects, Array_length(&objects), &stor);

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
