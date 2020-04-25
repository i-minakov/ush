#include "libmx.h"

// static char *join(char *s1, char *s2);

// char *mx_strjoin(char *s1, char *s2) {
//     char *s = NULL;
//     s = join(s1, s2);
//     if (s1 != NULL)
//         free(s1);
//     s1 = NULL;
//     return s;
// }

char *mx_strjoin(const char *s1,const char *s2) {
    if (s1 == NULL
        && s2 == NULL) return NULL;
    if (s1 == NULL
        || s2 == NULL) {
            if (s1 == NULL) return mx_strdup(s2);
            else return mx_strdup(s1);
        }
    char *p = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
    if (p == NULL) 
        return NULL;
    mx_strcpy(p, s1);
    mx_strcat(p, s2);
    return p;
}
