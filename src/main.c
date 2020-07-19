#include <stdio.h>
#include "AutoMalloc.h"

int main() {
	printf("Welcome to auto-malloc\n");
	//am_close();
	//am_status();
	am_start();
	am_status();

	int *pointer = new_int(65);
	printf("Value: %d\n", *pointer);
	*pointer = 5;
	printf("Value: %d\n", *pointer);
	char *char_pointer = new_char('d');
	printf("Value: %c\n", *char_pointer);
	char *char_pointer_2 = new_char('p');
	printf("Value: %c\n", *char_pointer_2);
	am_status();


	am_close();
}
