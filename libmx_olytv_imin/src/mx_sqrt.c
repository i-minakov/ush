#include "libmx.h"

int mx_sqrt(int x)
{
    if (x < 0) return 0;
    int i = 0;
    if (x == 1) return 1;
    for (i = 0; i <= x/2; i++) if (i*i == x) return i;
    return 0;
}
