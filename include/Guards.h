#ifndef GUARDS_H
#define GUARDS_H

/* OOM_GUARD handles the possibility that a null pointer 
 * is returned by a call to malloc, calloc, or realloc. In
 * the event of a null pointer, the program will terminate
 * and print to standard error */
void OOM_GUARD(void *ptr, char *file, int number);
#endif
