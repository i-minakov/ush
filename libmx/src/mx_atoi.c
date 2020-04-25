#include "libmx.h"

int mx_atoi(const char *s)
{
    int res = 0, n = 1;
    for (; *s; s++) {
        if (*s == '-') n = -1; 
        else {
            res = res*10 + (*s - '0');
        }
    }
    return res*n;
}
