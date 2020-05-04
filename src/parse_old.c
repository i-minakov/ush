#include "../inc/ush.h"

static char **check(char *line) {
    char **res = NULL;    
    char *tmp = NULL;

    if (mx_get_char_index(line, '\\') == -1)
        return mx_strsplit(line, ' ');
    free(line);
    res = mx_strsplit(tmp, '*');
    for (int i = 0; res[i]; i++)
        printf("%s\n", res[i]);
    return res;
}

void old_parse(char *line, t_ush *ush) {
    char *res = NULL;
    char **m = NULL;

    char **q = NULL;
    res = mx_strtrim(line);
    mx_strdel(&line);
    q = mx_strsplit(res, ';');
    for (int i = 0; q[i]; i++) {
        m = check(q[i]);
        ush->last_return = detect_builds(m, ush); 
        mx_del_strarr(&m);
    }
    mx_del_strarr(&q);
    free(res);
}
