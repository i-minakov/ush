#include "libmx.h"

void mx_printint(int n)
{
    if (n == 0) mx_printchar('0'); 
    if (n == -2147483648) {
        mx_printchar('-');
        mx_printchar('2');
        mx_printchar('1');
        mx_printchar('4');
        mx_printchar('7');
        mx_printchar('4');
        mx_printchar('8');
        mx_printchar('3');
        mx_printchar('6');
        mx_printchar('4');
        mx_printchar('8');
        return ;
    }
    if (n < 0) {
        n = -n;
        mx_printchar('-');
    }
    int num = n;
    int len = 0;
    for (; n; n /= 10) len++; 
    char r[len];
    len = len - 1;
    for (int i = 0; num; num /= 10, i++) r[i] = num%10 + '0';
    for (int i = len; i >= 0; i--) mx_printchar(r[i]);
}
