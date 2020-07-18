#include <stdio.h>
#include "AutoMalloc.h"

int main() {
	printf("Welcome to auto-malloc\n");
	//am_close();
	//am_status();
	am_start();
	am_status();

	int *pointer = new_int();
	printf("Value: %d\n", *pointer);
	*pointer = 5;
	printf("Value: %d\n", *pointer);

	am_close();
}
