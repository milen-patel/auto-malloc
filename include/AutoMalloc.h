#ifndef AUTOMALLOC_H
#define AUTOMALLOC_H
#include <stdio.h>

void am_start();
void am_close();
void am_status();
int* new_int();

typedef struct MemoryItem {
	size_t numBytes;
	void *memVal;
} MemoryItem;


#endif
