#include "libmx.h"

void *mx_realloc(void *ptr, size_t size) {
    unsigned char *r = NULL;
    if (size == 0) {
        free(ptr);
        ptr = NULL;
        return ptr;
    }
    if (ptr == NULL) r = malloc(size * sizeof(char));
    else {
        r = malloc(size * sizeof(char));
        mx_memcpy(r, ptr, size);
    }
    free(ptr);
    ptr = NULL;
    return r;
}
