#include "libmx.h"

void mx_printinterr(int n)
{
    if (n == 0) mx_printcharerr('0'); 
    if (n == -2147483648) {
        mx_printcharerr('-');
        mx_printcharerr('2');
        mx_printcharerr('1');
        mx_printcharerr('4');
        mx_printcharerr('7');
        mx_printcharerr('4');
        mx_printcharerr('8');
        mx_printcharerr('3');
        mx_printcharerr('6');
        mx_printcharerr('4');
        mx_printcharerr('8');
        return ;
    }
    if (n < 0) {
        n = -n;
        mx_printcharerr('-');
    }
    int num = n;
    int len = 0;
    for (; n; n /= 10) len++; 
    char r[len];
    len = len - 1;
    for (int i = 0; num; num /= 10, i++) r[i] = num%10 + '0';
    for (int i = len; i >= 0; i--) mx_printcharerr(r[i]);
}
