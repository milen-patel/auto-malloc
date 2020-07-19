#ifndef AUTOMALLOC_H
#define AUTOMALLOC_H
#include <stdio.h>
#include "AutoMalloc_String.h"



/* Used internally to keep track of user-allocated variables */
typedef enum VariableType {
	STANDARD = 0,
	STRING = 1,
} VariableType;

typedef struct MemoryItem {
	size_t numBytes;
	void *memVal;
	VariableType type;
} MemoryItem;

/* Starts AutoMalloc, must be called before any of the 'new' variable functions
 * are called. If am_start() is called then at any point during the program,
 * am_status() is allowed to be called. Before the termination of the program,
 * the am_close() function must be called in order to free all of the heap memory
 * that was allocated during the program from user calls or by implementation
 */
void am_start();

/* Ends AutoMalloc, must be called exactly one time after am_start() is called.
 * am_close() will automatically free any of the memory that was used during the
 * program related to AutoMalloc. This includes memory allocated from user calls
 * to the 'new' functions, as well as memory allocated during the implementation
 * of AutoMalloc.
 *
 * Once am_close() is called, the current AutoMalloc session is complete and 
 * all memory allocated before the function call no longer points to valid 
 * memory addresses. am_start() can be called again to begin another AutoMalloc
 * instance for the program; however, it does not make sense to do this (it would
 * be more practical to simply call am_close() once at the end of the program).
 */
void am_close();

/* Prints information regarding the status of AutoMalloc to standard out.
 * If AutoMalloc has been started and variables have been created using
 * AutoMalloc functions, a table will be printed containing general information
 * about all of the variables that AutoMalloc is currently tracking
 */
void am_status();

/* Creates a new AutoMalloc_String in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * AutoMalloc provides a custom implementation for Strings. Full documentation may
 * be viewed in AutoMalloc_String.h. AutoMalloc_Strings are dynamic in size and have
 * helper functions that make them preferrable to character arrays.
 *
 * width -> The initial number of characters to be stored in the string
 */
AutoMalloc_String *new_string(int width);

/* Creates a new char in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * startingValue -> The initial value that the char should be set to
 */
char *new_char(char startingValue);

/* Creates a new unsigned char in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * startingValue -> The initial value that the unsigned char should be set to
 */
unsigned char *new_unsigned_char(unsigned char startingValue);

/* Creates a new signed char in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * startingValue -> The initial value that the signed char should be set to
 */
signed char *new_signed_char(signed char startingValue);

/* Creates a new int in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * startingValue -> The initial value that the int should be set to
 */
int *new_int(int startingValue);

/* Creates a new unsigned int in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * startingValue -> The initial value that the unsigned int should be set to
 */
unsigned int *new_unsigned_int(unsigned int startingValue);

/* Creates a new short in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * startingValue -> The initial value that the short should be set to
 */
short *new_short(short startingValue);

/* Creates a new unsigned short in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * startingValue -> The initial value that the unsigned short should be set to
 */
unsigned short *new_unsigned_short(unsigned short startingValue);

/* Creates a new long in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * startingValue -> The initial value that the long should be set to
 */
long *new_long(long startingValue);

/* Creates a new unsigned long in heap memory. am_start() must have been called
 * in the program prior to calling this function.
 *
 * startingValue -> The initial value that the unsigned long should be set to
 */
unsigned long *new_unsigned_long(unsigned long startingValue);

#endif
