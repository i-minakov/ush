#include "libmx.h"

char *mx_file_to_str(const char *file) {
    if (file == NULL) return NULL;
    char buff[1];
    long arr = 0;
    int open_file = open(file, O_RDONLY);
    if (open_file < 0) return NULL;
    int read_file = read(open_file, buff, 1);
    if (read_file < 0) return NULL;
    while (read_file > 0) {
        read_file = read(open_file, buff, 1);
        arr++;
    }
    close(open_file);
    char *p = mx_strnew(arr - 1);
    char suf[1];
    int i = 0;
    open_file = open(file, O_RDONLY);
    if (open_file < 0) return NULL;
    read_file = read(open_file, suf, 1);
    if (read_file < 0) return NULL;
    while (read_file > 0) {
        p[i] = suf[0];
        read_file = read(open_file, suf, 1);
        i++;
    }
    close(open_file);
    return p;
}
