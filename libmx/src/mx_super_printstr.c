#include "libmx.h"

void mx_super_printstr(char *st) {
    if (st == NULL) 
        return ;
    write(1, st, mx_strlen(st));
    free(st);
    st = NULL;
}
