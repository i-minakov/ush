#include "libmx.h"

char *mx_itoa(unsigned long long number) {
    long int i = 1;
    char *rez = NULL;
    
    if (number == 0) {
        rez = mx_strdup("0");
        return rez;
    }
    for (long n = (number < 0) ? (long) number * -1 : number; n;
        n /= 10, i++);
    i = number < 0 ? i++ : i - 1;
    rez = mx_strnew(i);
    for (long n = (number < 0) ? (long) number * -1 : number; n;
        rez[i - 1] = n % 10 + '0', n /= 10, i--);
    if (number < 0)
        rez[0] = '-';
    return rez;
}

// char *mx_itoa(long long number)
// {
//     if (number == 0) {
//         char *r = mx_strnew(1);
//         r[0] = '0';
//         return r;
//     }
//     if (number == -2147483648) {
//         char *r = "-2147483648";
//         return r;
//     }
//     long long num = number;
//     int len = 0, f = 0;
//     for (; num; num /= 10) len++;
//      if (number < 0) {
//         number = -number;
//         f = 1;
//     }
//     char *res = mx_strnew(len + 1);
//     int i;
//     for (f == 1 ? i = len : (i = len - 1); i >= 0; i--, number /= 10) {
//         res[i] = number%10 + '0';
//         if (f == 1 && i == 0) res[i] = '-'; 
//     }
//     return res;
// }
