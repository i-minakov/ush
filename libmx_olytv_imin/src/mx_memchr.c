#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n)
{
    unsigned char *r = (unsigned char *)s;
    for (; n--; ) {
        if (*r == c) return r;
        r++;
    }
    return NULL;
}
