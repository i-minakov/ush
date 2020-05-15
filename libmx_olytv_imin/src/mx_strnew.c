#include "libmx.h"

char *mx_strnew(const int size)
{
    char *res = (char *)malloc(sizeof(char) * (size + 1));
    for (int i = 0; i <= size; i++) res[i] = '\0';
    return res;
}
