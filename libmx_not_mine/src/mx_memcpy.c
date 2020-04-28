#include "libmx.h"

void *mx_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
    for (unsigned char *t = dst, *s = (unsigned char *)src; n--; ) {
        *t = *s;
        t++;
        s++;
    }
    return dst;
}
