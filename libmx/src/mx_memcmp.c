#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n)
{
    unsigned char *r1 = (unsigned char *)s1;
    unsigned char *r2 = (unsigned char *)s2;
    for (; n--; ) {
        if (*r1 != *r2) return *r1 - *r2;
            r1++;
            r2++;
    }
    return 0;
}
