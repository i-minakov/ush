#include "libmx.h"

char *mx_nbr_to_hex(unsigned long num)
{
    int count = 0, i = 0, j = 0;
    for (i = num; i != 0; i /= 16)
        count++;
    char *s = mx_strnew(count);
    for (i = num; i != 0; i /= 16) {
        if (i % 16 > 9)
            s[j] = i % 16 + 87;
        else
            s[j] = i % 16 + '0';
        j++;
    }
    mx_str_reverse(s);
    return s;
}
