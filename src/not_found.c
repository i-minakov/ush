#include "../inc/ush.h"

int not_found(char *args, char *str) {
    //fg: job not found: fsh
    write(1, str, mx_strlen(str));
    write(1, " not found: ", 12);
    write(1, args, mx_strlen(args));
    write(1, "\n", 1);
    return 1;
}
