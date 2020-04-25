#include "libmx.h"

char *mx_strdup(const char *str)
{
    int len = mx_strlen(str);
    char *res = mx_strnew(len);
    mx_strcpy(res, str);
    return res;
}
