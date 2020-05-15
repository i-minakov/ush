#include "libmx.h"

 int mx_strcmp(const char *s1, const char *s2)
 {
    if(s1 == NULL) return -1;
    if(s2 == NULL) return 1;
    while (*s1 || *s2)
    {
        if (*s1 != *s2) return *s1 - *s2;
        s1++;
        s2++;
    } 
    return 0;
 }
