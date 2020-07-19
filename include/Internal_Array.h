#ifndef VEC_H
#define VEC_H

#include <stdlib.h>
#include <stdbool.h>

/* Array is an abstraction representing a growabale, dynamic
 * array. Members of a Array are not meant to be accessed directly,
 * and thus Array interaction should be performed strictly using the
 * methods listed in this header file.  */

typedef struct Array {
    size_t item_size; /* size of an item in bytes */
    size_t length;    /* number of items in Array */
    size_t capacity;  /* number of items buffer can store */
    void *buffer;     /* heap memory storing items */
} Array;

/* Constructor / Destructor */

/**
 * Construct a Array value. Owner is responsible for calling
 * Array_drop when its lifetime expires.
 *
 * @param capacity - initial number of items it can store
 * @param item_size - sizeof an individual item
 * @return initialized Array value.
 */
Array Array_value(size_t capacity, size_t item_size);

/**
 * Owner must call to expire a Array value's lifetime.
 * Frees any heap memory the Array owns.
 * Resets length, capacity to zero, buffer to NULL.
 */
void Array_drop(Array *self);

/* Accessors */

/**
 * Returns the number of items in the Array.
 */
size_t Array_length(const Array *self);

/**
 * Get a pointer to the item at `index`. You may
 * write to this reference, but not beyond it.
 *
 * The lifetime of this reference expires as soon
 * as any other write operation is performed outside
 * of it because the Array may relocate its buffer
 * when it runs out of space.
 */
void* Array_ref(const Array *self, size_t index);

/* Operations */

/**
 * Copy the item at `index` to the memory of `out`. Attempting
 * to access an invalid index will result in an out of bounds
 * crash.
 */
void Array_get(const Array *self, size_t index, void *out);

/**
 * Assign an item at `index` to be a copy of `value`.
 * Valid indices include 0-length. When the index is equal
 * to length, the item is appended to the Array. Attempting
 * to assign to an `index` greater than length will result
 * in an out of bounds crash.
 */
void Array_set(Array *self, size_t index, const void *value);

/**
 * Compare deep equality with another Array. Should return true
 * if Arrays are equal in length and buffer content.
 */
bool Array_equals(const Array *self, const Array *other);

/**
 * Starting from `index`, remove `delete_count` items from `self`'s buffer, 
 * and insert `insert_count` values from `items` at that index of `self`.
 * All items inserted become owned by the `Array`.
 *
 * This is a swiss army knife function for inserting, removing, and overwriting
 * items with a `Array`.
 *
 * Attempting to delete beyond the end of the Array's elements or insert beyond
 * the length of the Array will result in an out of bounds crash.
 *
 * Example - Given:
 * 1. a Array `v` with elements [100, 200, 300, 400] and an int[] a 
 * 2. an array `a` with elements [800, 900]
 * The following examples are indepentent and assume the starting values above.
 * Call:                        | v's Items after:
 * Array_splice(&v, 2, 0, a, 2)   | [100, 200, 800, 900, 300, 400]
 * Array_splice(&v, 2, 1, a, 2)   | [100, 200, 800, 900, 400]
 * Array_splice(&v, 0, 0, a, 2)   | [800, 900, 100, 200, 300, 400]
 * Array_splice(&v, 0, 3, a, 1)   | [800, 400]
 */
void Array_splice(
        Array *self, 
        size_t index, 
        size_t delete_count, 
        const void *items, 
        size_t insert_count
        );

#endif
