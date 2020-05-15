#include "libmx.h"

static bool m_isspace(char c) {
    return (c == ' ' 
            || c == '\n'
            || c == '\t'
            || c == '\v'
            || c == '\f'
            || c == '\r');
}


char *mx_del_extra_spaces(const char *str) {
    if (!str) return NULL;
    int f = 0, len = 0;
    str = mx_strtrim(str);
    for (int i = 0; str[i]; i++) {
        if (m_isspace(str[i]) && f == 0) {
            f = 1; 
            len++;
        }
        if (m_isspace(str[i]) && f == 1) continue;
        else {
            len++; f = 0;
        }
    }
    char *rez = (char *)malloc(len);
    int i = 0;
    for (int u = 0; str[u]; u++) {
        if(!m_isspace(str[u])){
        rez[i] = str[u];
        i++;
        }
        else if(m_isspace(str[u]) && !m_isspace(str[u - 1])) {
           rez[i] = ' ';
        i++; 
        }
        else continue;
    }
    return rez;
}
