#include "libmx.h"

char *mx_nbr_to_hex(unsigned long nbr)
{
    int len = 0;
    unsigned long num = nbr;
    for (; num; num /= 16) len++;
    char *res = malloc(len);
    for (int i = len - 1; i >= 0; i--, nbr /= 16) {
        int ost = nbr%16;
        if (ost > 9) res[i] = ost + 87;
        else res[i] = nbr%16 + '0';
    } 
    return (char *)res;
}
