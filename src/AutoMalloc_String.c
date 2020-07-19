#include <string.h>
#include <stdio.h>
#include "AutoMalloc_String.h"
#include "Internal_Array.h"

static char NULL_CHAR = '\0';

/* Helper function that will terminate the program with an appropriate
 * error message, given a line reference to the error */
static void exitOnError(unsigned line);

AutoMalloc_String AutoMalloc_String_value(size_t capacity)
{
    AutoMalloc_String s = Array_value(capacity + 1, sizeof(char));
    Array_set(&s, 0, &NULL_CHAR);
	return s;
}

void AutoMalloc_String_drop(AutoMalloc_String *self)
{
    Array_drop(self);
}

size_t AutoMalloc_String_length(const AutoMalloc_String *self)
{
    return Array_length(self) - 1;
}

const char* AutoMalloc_String_cstr(const AutoMalloc_String *self)
{
    return (char*) Array_ref(self, 0);
}

char* AutoMalloc_String_ref(const AutoMalloc_String *self, const size_t index)
{
    return (char*) Array_ref(self, index);
}

AutoMalloc_String AutoMalloc_String_from(const char *cstr) {
    AutoMalloc_String newStr = AutoMalloc_String_value(1);
    int i = 0;
    while (*(cstr+i) != NULL_CHAR) {
        Array_set(&newStr, i, cstr+i); 
        i++;
    }
    /* Append the null character */
    Array_set(&newStr, i, &NULL_CHAR); 
    return newStr;
}

void AutoMalloc_String_splice(AutoMalloc_String *self,size_t index,size_t delete_count,const char *cstr, size_t insert_count) {
   if (delete_count+index > AutoMalloc_String_length(self)) {
        exitOnError(__LINE__);
   } else if (index > AutoMalloc_String_length(self)) {
        exitOnError(__LINE__);
   }
    Array_splice(self, index, delete_count, cstr, insert_count);
}

void AutoMalloc_String_append(AutoMalloc_String *self, const char *cstr) {
    size_t cstrlength = 0;
    while (*(cstr + cstrlength) != NULL_CHAR) {
        cstrlength++;
    }
    AutoMalloc_String_splice(self, AutoMalloc_String_length(self), 0, cstr, cstrlength);
}

char AutoMalloc_String_get(const AutoMalloc_String *self, size_t index){
    if ((index<0) || (index>=AutoMalloc_String_length(self))) {
        exitOnError(__LINE__);
    }
    return *((char*)Array_ref(self,index));
}

void AutoMalloc_String_set(AutoMalloc_String *self, size_t index, const char value){
   if(index < AutoMalloc_String_length(self)) {
        AutoMalloc_String_splice(self, index, 1, &value, 1);
   } else if (index == AutoMalloc_String_length(self)) {
        AutoMalloc_String_splice(self,index,0, &value, 1);
   } else {
      exitOnError(__LINE__); 
   }
}

/* Helper Functions */
static void exitOnError(unsigned line) {
    fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, line);
    exit(EXIT_FAILURE);
}
