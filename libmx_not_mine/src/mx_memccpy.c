#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n)
{
    unsigned char *cdst = (unsigned char *)dst,
        *csrc = (unsigned char *)src;

    for (size_t i = 0; *csrc != (unsigned char)c && i < n; i++)
        *cdst++ = *csrc++;

    if (*csrc == c)
    {
        *cdst = c;
        return cdst + 1;
    }
    return NULL;
}
