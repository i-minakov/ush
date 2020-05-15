#include "libmx.h"


void mx_print_strarr(char **arr, const char *delim) {
    for (int i = 0; arr[i]; i++)
    {
        write(1, arr[i], mx_strlen(arr[i]));
        if (arr[i + 1]) write(1, delim, mx_strlen(delim));
    }
    write(1, &("\n"), 1);
}
