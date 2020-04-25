#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) 
{
    if (str == NULL || sub == NULL) return -1;
    int f = 0, res = 0;
    for (int i = 0, j = 0; str[i]; i++)
    {
        if (str[i] == sub[j]) {
            f++;
            j++;
        }
        if (f == mx_strlen(sub) ) {
            res++;
            f = 0;
            j = 0;
        }
    }
    if (res > 0) return res; 
    else return -1;
}
