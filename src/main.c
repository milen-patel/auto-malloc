#include <stdio.h>
#include "AutoMalloc.h"

int main() {
	printf("Welcome to auto-malloc\n");

	/* Attempt to close AutoMalloc before starting.
	 * Will result in a failed messaged being printed
	 */
	am_close();

	/* Call the status of AutoMalloc before starting.
	 * Will print 'Not Running' to the screen since
	 * there is no active AutoMalloc instance running.
	 */
	am_status();

	/* Start AutoMalloc, should print nothing */
	am_start();

	/* Call the status, should display that we are running
	 * but have no active variables
	 */
	am_status();

	/* Create a new integer with value of 65 */
	int *pointer = new_int(65);

	/* Print the value to the screen */
	printf("[Expected: 65] Value: %d\n", *pointer);

	/* Change the value of the pointer */
	*pointer = 5;

	/* Print new value to screen */
	printf("[Expected: 5] Value: %d\n", *pointer);

	/* Create a character pointer with value 'd' */
	char *char_pointer = new_char('d');

	/* Print the value to the screen */
	printf("[Expected: d] Value: %c\n", *char_pointer);

	/* Change the value of the pointer */
	*char_pointer = 'f';

	/* Print the updated value to the screen */
	printf("[Expected: f] Value: %c\n", *char_pointer);

	/* Create a AutoMalloc_String */
	AutoMalloc_String *strPtr;
	strPtr = new_string(2);
	AutoMalloc_String_append(strPtr, "This is a sample string!");

	/* Print the value of the string to the screen */
	printf("%s\n", AutoMalloc_String_cstr(strPtr));

	/* Call the status function, should print a table with active variables */
	am_status();

	/* Close AutoMalloc */
	am_close();
}
