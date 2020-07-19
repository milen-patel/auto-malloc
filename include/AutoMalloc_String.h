#ifndef STR_H
#define STR_H

#include "Internal_Array.h"

/**
 * AutoMalloc_String is just an alias of Array to make its purpose of storing
 * char data and the following functions clear.
 */
typedef Array AutoMalloc_String;

/**
 * Construct an empty AutoMalloc_String value. Owner is responsible for calling
 * AutoMalloc_String_drop when its lifetime expires.
 */
AutoMalloc_String AutoMalloc_String_value(size_t capacity);

/**
 * Owner of a AutoMalloc_String must call to expire its buffer data's lifetime.
 * Frees any heap memory the AutoMalloc_String owns.
 */
void AutoMalloc_String_drop(AutoMalloc_String *self);

/**
 * Returns the length of the AutoMalloc_String _not_ including the null terminating
 * character.
 */
size_t AutoMalloc_String_length(const AutoMalloc_String *self);

/**
 * Returns a pointer to a character at a specific offset. Caller is
 * free to modify the memory address returned, but not beyond it.
 */
char* AutoMalloc_String_ref(const AutoMalloc_String *self, size_t index);

/**
 * Returns a pointer to the first character of the AutoMalloc_String's buffer.
 * Returned value should be used for read purposes only. To mutate
 * the AutoMalloc_String, make use of AutoMalloc_String_splice, AutoMalloc_String_append, or AutoMalloc_String_set.
 */
const char* AutoMalloc_String_cstr(const AutoMalloc_String *self);

/**
 * Construct a new AutoMalloc_String value from a C-string. AutoMalloc_String_from will _copy_
 * the `cstr` contents to a new heap allocated buffer. Caller is 
 * responsible for calling AutoMalloc_String_drop when its lifetime expires.
 *
 * Usage: AutoMalloc_String s = AutoMalloc_String_from("hello, world");
 */
AutoMalloc_String AutoMalloc_String_from(const char *cstr);

/**
 * Starting from `index`, remove `delete_count` items from `self`,
 * and insert `insert_count` values from `cstr` at that index of `self`.
 */
void AutoMalloc_String_splice(
        AutoMalloc_String *self,
        size_t index,
        size_t delete_count,
        const char *cstr,
        size_t insert_count
     );

/**
 * Append a C-string to a AutoMalloc_String. Will dynamically grow the AutoMalloc_String's 
 * memory allocation to be able to store the cstr's character
 * contents if necessary.
 */
void AutoMalloc_String_append(AutoMalloc_String *self, const char *cstr);

/**
 * Get a character at a specific index of the AutoMalloc_String.
 */
char AutoMalloc_String_get(const AutoMalloc_String *self, size_t index);

/**
 * Set a character at a specific index of the AutoMalloc_String. If the index
 * is the length of the AutoMalloc_String, it will append the character to the
 * end of the AutoMalloc_String and terminate with a null character.
 */
void AutoMalloc_String_set(AutoMalloc_String *self, size_t index, const char value);

#endif
