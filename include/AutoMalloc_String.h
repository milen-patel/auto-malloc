#ifndef STR_H
#define STR_H

#include "Internal_Array.h"

/**
 * Str is just an alias of Array to make its purpose of storing
 * char data and the following functions clear.
 */
typedef Array Str;

/**
 * Construct an empty Str value. Owner is responsible for calling
 * Str_drop when its lifetime expires.
 */
Str Str_value(size_t capacity);

/**
 * Owner of a Str must call to expire its buffer data's lifetime.
 * Frees any heap memory the Str owns.
 */
void Str_drop(Str *self);

/**
 * Returns the length of the Str _not_ including the null terminating
 * character.
 */
size_t Str_length(const Str *self);

/**
 * Returns a pointer to a character at a specific offset. Caller is
 * free to modify the memory address returned, but not beyond it.
 */
char* Str_ref(const Str *self, size_t index);

/**
 * Returns a pointer to the first character of the Str's buffer.
 * Returned value should be used for read purposes only. To mutate
 * the Str, make use of Str_splice, Str_append, or Str_set.
 */
const char* Str_cstr(const Str *self);

/**
 * Construct a new Str value from a C-string. Str_from will _copy_
 * the `cstr` contents to a new heap allocated buffer. Caller is 
 * responsible for calling Str_drop when its lifetime expires.
 *
 * Usage: Str s = Str_from("hello, world");
 */
Str Str_from(const char *cstr);

/**
 * Starting from `index`, remove `delete_count` items from `self`,
 * and insert `insert_count` values from `cstr` at that index of `self`.
 */
void Str_splice(
        Str *self,
        size_t index,
        size_t delete_count,
        const char *cstr,
        size_t insert_count
     );

/**
 * Append a C-string to a Str. Will dynamically grow the Str's 
 * memory allocation to be able to store the cstr's character
 * contents if necessary.
 */
void Str_append(Str *self, const char *cstr);

/**
 * Get a character at a specific index of the Str.
 */
char Str_get(const Str *self, size_t index);

/**
 * Set a character at a specific index of the Str. If the index
 * is the length of the Str, it will append the character to the
 * end of the Str and terminate with a null character.
 */
void Str_set(Str *self, size_t index, const char value);

#endif
