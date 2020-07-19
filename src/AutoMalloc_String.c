#include <string.h>
#include <stdio.h>
#include "AutoMalloc_String.h"
#include "Internal_Array.h"

static char NULL_CHAR = '\0';

/* Helper function that will terminate the program with an appropriate
 * error message, given a line reference to the error */
static void exitOnError(unsigned line);

Str Str_value(size_t capacity)
{
    Str s = Array_value(capacity + 1, sizeof(char));
    Array_set(&s, 0, &NULL_CHAR);
	return s;
}

void Str_drop(Str *self)
{
    Array_drop(self);
}

size_t Str_length(const Str *self)
{
    return Array_length(self) - 1;
}

const char* Str_cstr(const Str *self)
{
    return (char*) Array_ref(self, 0);
}

char* Str_ref(const Str *self, const size_t index)
{
    return (char*) Array_ref(self, index);
}

Str Str_from(const char *cstr) {
    Str newStr = Str_value(1);
    int i = 0;
    while (*(cstr+i) != NULL_CHAR) {
        Array_set(&newStr, i, cstr+i); 
        i++;
    }
    /* Append the null character */
    Array_set(&newStr, i, &NULL_CHAR); 
    return newStr;
}

void Str_splice(Str *self,size_t index,size_t delete_count,const char *cstr, size_t insert_count) {
   if (delete_count+index > Str_length(self)) {
        exitOnError(__LINE__);
   } else if (index > Str_length(self)) {
        exitOnError(__LINE__);
   }
    Array_splice(self, index, delete_count, cstr, insert_count);
}

void Str_append(Str *self, const char *cstr){
    size_t cstrlength = 0;
    while (*(cstr + cstrlength) != NULL_CHAR) {
        cstrlength++;
    }
    Str_splice(self, Str_length(self), 0, cstr, cstrlength);
}

char Str_get(const Str *self, size_t index){
    if ((index<0) || (index>=Str_length(self))) {
        exitOnError(__LINE__);
    }
    return *((char*)Array_ref(self,index));
}

void Str_set(Str *self, size_t index, const char value){
   if(index < Str_length(self)) {
        Str_splice(self, index, 1, &value, 1);
   } else if (index == Str_length(self)) {
        Str_splice(self,index,0, &value, 1);
   } else {
      exitOnError(__LINE__); 
   }
}

/* Helper Functions */
static void exitOnError(unsigned line) {
    fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, line);
    exit(EXIT_FAILURE);
}
