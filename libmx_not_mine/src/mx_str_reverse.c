#include "libmx.h"

void mx_str_reverse(char *s)
{
    int len = mx_strlen(s);
    for (int i = 0, j = len - 1; i < j; i++, j--)
    {
        mx_swap_char(s + i,  s + j);
    }
}
