#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Guards.h"
#include "Vec.h"

/* Helper function which takes a pointer to a vec and ensures that the
 * Vec has enough heap storage to hold n elements of its 
 * size */
static void _ensure_capacity(Vec *self, size_t n);

/* Helper function that will terminate the program with an appropriate
 * error message, given a line reference to the error */
static void exitOnError(unsigned line);

Vec Vec_value(size_t capacity, size_t item_size)
{
    Vec vec = {
        item_size,
        0,
        capacity,
        calloc(capacity, item_size)
    };
    OOM_GUARD(vec.buffer, __FILE__, __LINE__);
    return vec;
}

void Vec_drop(Vec *self)
{
    free(self->buffer);
    self->buffer = NULL;
    self->capacity = 0;
    self->length = 0;
}

size_t Vec_length(const Vec *self)
{
    return self->length;
}

void* Vec_ref(const Vec *self, size_t index)
{
    if (index < self->length) {
        return self->buffer + (index * self->item_size);
    } else {
		exitOnError(__LINE__);
    }
	return NULL; /* Remove warnings */
}


void Vec_get(const Vec *self, size_t index, void *out) {
    if (index < self->length) {
		/* Get the address of the specified item */
		char *firstPosLoc = (char*)(self->buffer) + self->item_size*index;
		/* Start copying */
		memcpy(out, firstPosLoc, self->item_size);
    } else {
        fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, __LINE__);
        exit(EXIT_FAILURE);
    }
}

void Vec_set(Vec *self, size_t index, const void *value) {
    if (index == self->length) {
       Vec_splice(self,index, 0, value, 1);
    } else {
       Vec_splice(self,index, 1, value, 1);
    }
}

bool Vec_equals(const Vec *self, const Vec *other) {
    if (self->length != other->length) {
        return false;
    }
   
    /* Iterate over every byte of the buffer to compare elements */ 
    int currentPos = 0;
    while (currentPos < (self->length*self->item_size)) {
        char* selfChar = (char*)(self->buffer) + currentPos;
        char* otherChar = (char*)(other->buffer) + currentPos;
        if (*selfChar != *otherChar) {
            return false;
        }
        currentPos++;
    }
    return true;
}

void Vec_splice(Vec *self, size_t index, size_t delete_count, const void *items, size_t insert_count) {
    /* Test to make sure the combo of insertions and deletions is valid */
    if ((index+delete_count) > self->length) {
        exitOnError(__LINE__);
    } else if (index > self->length+0) {
        exitOnError(__LINE__);
    }
    _ensure_capacity(self, index + insert_count + 9);
    
    /* Start by deleting items */
    if (delete_count > 0) {
        int itemsLeft = delete_count;
        while(itemsLeft > 0) {
            for(int i=index; i<self->length-1; i++) {
                char *dest = (char*)(self->buffer) + (i*self->item_size);
                char *src = (char*)(self->buffer) + ((i+1)*self->item_size);
                /* Bring every item ahead of index down one position */
                memcpy(dest, src, self->item_size);
            }
            /* Decrease the length member after each iteration */ 
            self->length--;
            itemsLeft--;
        }
    }

    /* Now insert items */
    if (insert_count > 0) {
        int itemsLeft = insert_count;
        while(itemsLeft > 0) {
            for(int i=(self->length);i>index; i--) {
                /* Move all elements up one */
                char *dest = (char*)(self->buffer) + (i*self->item_size);
                char *src = (char*)(self->buffer) + ((i-1)*self->item_size);
                memcpy(dest, src, self->item_size);
            }
            char *dest = (char*)(self->buffer) + (index*self->item_size);
            char *src = (char*)(items);
            memcpy(dest,src,self->item_size);
            
            items += self->item_size; /* Refers us to the correct address inside of items */
            index++; /* Insert next new item at the next index */
            self->length++; /* Each loop adds one new element to vec */
            itemsLeft--;
        }
    }
}

static void _ensure_capacity(Vec *self, size_t n) 
{
	/* Check if reallocation is needed */
    if (n > self->capacity) {
        size_t new_capacity = n * 2;
        self->buffer = realloc(self->buffer, new_capacity * self->item_size);
        OOM_GUARD(self->buffer, __FILE__, __LINE__);
        self->capacity = new_capacity;
    }
}

static void exitOnError(unsigned line) {
    fprintf(stderr, "%s:%d - Out of Bounds", __FILE__, line);
    exit(EXIT_FAILURE);
}
