#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len){

    unsigned char *s;
    unsigned  char *lasts;
    unsigned char  *d;
    unsigned char *lastd;

    d = (unsigned char *) dst;
    s = (unsigned char *) src;
    if ( mx_strlen((char *)d) > mx_strlen((char *)s)){
        while (len--)
            *d++ = *s++;
    }
    else
    {
        lasts = s + (len - 1);
        lastd = d + (len - 1);
        while (len--)
            *lastd-- = *lasts--;
    }
    return (char *) dst;
}

