#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n)
{
    unsigned char *r = (unsigned char *)s;
    while (*r) r++;
    for (; n--;) {
        if (*r == c) return r;
        r--;
    }
    return NULL;
}
