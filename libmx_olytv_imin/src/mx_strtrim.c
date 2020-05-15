#include "libmx.h"

static bool m_isspace(char c) {
    return (c == ' ' 
            || c == '\n'
            || c == '\t'
            || c == '\v'
            || c == '\f'
            || c == '\r');
}


char *mx_strtrim(const char *str) {
    if (str == NULL) return NULL;
    int left;
    int right;
    left = 0;
    right = mx_strlen(str);
    for (int i = 0; m_isspace(str[i]); i++, left++);
    for (int i = mx_strlen(str) - 1; m_isspace(str[i]); i--, right--);
    // if (left == 0
    //     && right == mx_strlen(str)) return NULL;
    char *p = mx_strnew(right - left);
    if ((right - left) <= 0) {
        char *r = "\0";
        return r;
    }
    mx_strncpy(p, &str[left], right - left);
    return p;
}
