#include <stdlib.h>
#include <stdio.h>

void OOM_GUARD(void *ptr, char *file, int number)
{
    if (ptr == NULL) {
        fprintf(stderr, "%s:%d Out of Memory", file, number);
        exit(EXIT_FAILURE);
    }

}

