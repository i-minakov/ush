#include "libmx.h"

void mx_printstr(const char *s)
{
    for (; *s; s++) write(1, s, 1);
}
