# AutoMalloc 
                              
 AutoMalloc is a program that facilitates the use of C's heap functions (malloc and free) by keeping track of variables and automatically freeing them at the end of the program
 
---
# Testing it Out

An example program has been included (src/main.c) to demonstrate some example usage of AutoMalloc. To test it out, simply clone the project and compile everything together. Additionally, a makefile has been included. `make all` will create a build/ directory and compile all of the files. `make run` will execute the main demonstration program. `make clean` will remove all files from the /build direcory. 

If you would like to very that AutoMalloc is not leaking any memory, then `make leak-test` will run the demonstration program through valgrind which will show no memory leaks!

# Using AutoMalloc in Your Own Program

If you would like to use AutoMalloc in your own program, add all of the files in src/ and header/ with the exception of src/main.c.

# How to use AutoMalloc

##### There are two essential functions that must be called if you wish to use AutoMalloc.

**`am_start()`**: Starts AutoMalloc, must be called before any of the 'new' variable functions are called. If am_start() is called then at any point during the program, am_status() is allowed to be called which will print information regarding the current variables being tracked by AutoMalloc. Before the termination of the program, the `am_close()` function must be called in order to free all of the heap memory that was allocated during the program from user calls or by implementation

**`am_close()`**: Ends AutoMalloc, must be called exactly one time after `am_start()` is called. `am_close()` will automatically free any of the memory that was used during the program related to AutoMalloc. This includes memory allocated from user calls to the 'new' functions, as well as memory allocated during the implementation of AutoMalloc. Once `am_close()` is called, the current AutoMalloc session is complete and all memory allocated before the function call no longer points to valid memory addresses. `am_start()` can be called again to begin another AutoMalloc instance for the program; however, it does not make sense to do this (it would be more practical to simply call `am_close()` once at the end of the program).

##### Additionally, there is another function that will inform you about the current status of AutoMalloc.
**`am_status()`**: Prints information regarding the status of AutoMalloc to standard out. If AutoMalloc has been started and variables have been created using AutoMalloc functions, a table will be printed containing general information about all of the variables that AutoMalloc is currently tracking.

##### Creating variables within AutoMalloc
Once you have called am_start(), you must use the AutoMalloc functions to create variables, or else they will not be tracked by AutoMalloc. You may allocate heap space however you want, but only variables created using AutoMalloc functions will be automatically freed.

Using any of the creation functions will give you a pointer to a specified variable, you must NOT free any of these variables yourself. AutoMalloc will free memory for you when you call `am_close()`. Additionally, `am_start()` must have been called before any of these creation functions are called, or else you will get an error (similarly, `am_close()` must not have been called before any of the creation functions).

**`AutoMalloc_String *new_string(int width)`**: Creates a new AutoMalloc_String in heap memory. `am_start()` must have been called in the program prior to calling this function. AutoMalloc provides a custom implementation for Strings. Full documentation may be viewed in AutoMalloc_String.h. AutoMalloc_Strings are dynamic in size and have helper functions that make them preferrable to character arrays. The width parameter represents the initial number of characters to be stored in the string

The following functions create new variables of the specified type and return pointers to them. You are free to dereferene and modify the underlying values represented by the pointer. Full documentation for all of the following functions is specified in AutoMalloc.h

**`char *new_char(char startingValue)`**
**`unsigned char *new_unsigned_char(unsigned char startingValue)`**
**`signed char *new_signed_char(signed char startingValue)`**
**`int *new_int(int startingValue)`**
**`unsigned int *new_unsigned_int(unsigned int startingValue)`**
**`short *new_short(short startingValue)`**
**`unsigned short *new_unsigned_short(unsigned short startingValue)`**
**`long *new_long(long startingValue)`**
**`unsigned long *new_unsigned_long(unsigned long startingValue)`**

