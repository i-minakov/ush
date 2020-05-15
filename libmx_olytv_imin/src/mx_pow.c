#include "libmx.h"

double mx_pow(double n, unsigned int pow)
{
    if (pow == 0) return 1;
    double res = 1;
    for (;pow; pow--) res*=n;
    return res;
}
