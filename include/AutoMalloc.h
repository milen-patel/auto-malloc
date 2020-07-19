#ifndef AUTOMALLOC_H
#define AUTOMALLOC_H
#include <stdio.h>

void am_start();
void am_close();
void am_status();

char *new_char(char startingValue);
unsigned char *new_unsigned_char(unsigned char startingValue);
signed char *new_signed_char(signed char startingValue);
int *new_int(int startingValue);
unsigned int *new_unsigned_int(unsigned int startingValue);
short *new_short(short startingValue);
unsigned short *new_unsigned_short(unsigned short startingValue);
long *new_long(long startingValue);
unsigned long *new_unsigned_long(unsigned long startingValue);

typedef struct MemoryItem {
	size_t numBytes;
	void *memVal;
} MemoryItem;


#endif
