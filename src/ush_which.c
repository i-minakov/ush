#include "../inc/ush.h"

int check_access(char **m, char *args) {
    char *tmp = NULL;
    int f = 0;

    for (int i = 0; m[i]; i++) {
        tmp = mx_strjoin(m[i], "/");
        tmp = mx_delit_fre(tmp, args);
        if (access(tmp, F_OK) == 0) {
            mx_printstr(tmp);
            write(1, "\n", 1);
            f = 1;
            break ;
        }
        mx_strdel(&tmp);
    }
    mx_strdel(&tmp);
    return f;
}

int ush_which(char **args) {
    char *path = getenv("PATH");
    char **m = NULL;
    char *tmp = NULL;
    int f = 0;
    
    if (args[1] == NULL)
        return 1;
    m = mx_strsplit(path, ':');
    for ( args++; *args; args++) {
        f = check_access(m, *args);
        if (f != 1) {
            mx_printstr(*args);
            write(1, " not found\n", 11);
        }
        f = 0;
    }
    mx_del_strarr(&m);
    return 1;
}
