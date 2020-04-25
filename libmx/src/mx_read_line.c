#include "libmx.h"

int mx_read_line(char **lineptr, int buf_size, char delim, const int fd) {
    char *s;
    char buf[buf_size + 1];
    int flag_out = 0;
    int size = 0;
    if (fd < 0) {
        return -1;
    }
    while (read(fd, buf, buf_size)) {
        int i = 0;
        for ( ; i < buf_size; i++, size++) {
            if (buf[i] == delim) {
                flag_out = 1;
                for (int j = i; j <= buf_size; j++) buf[j] = '\0';
                break;
            }
        }
        s = *lineptr;
        *lineptr = mx_strjoin(*lineptr, buf);
        free(s);
        if (flag_out) break;
    }
    if (!read(fd, buf, buf_size) && !flag_out) {
        size = 0;
        free(*lineptr);
        *lineptr = "";
    }
    return size;
}
