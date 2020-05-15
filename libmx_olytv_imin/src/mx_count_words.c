#include "libmx.h"

int mx_count_words(const char *str, char c) {
    if (str == NULL || *str == 0) return -1;
    int count = 0, f = 0;
    for (int i = 0; *str; i++, str++) {
        if (*str == c && f == 0) continue;
        else {
            f = 1;
            if (*str == c && f == 1) {
                f = 0;
                count ++;
            }
        }
    }
    if (f == 1) count++;
    return count;
}
