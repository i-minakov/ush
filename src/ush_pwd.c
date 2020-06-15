#include "../inc/ush.h"

int mx_ush_pwd(char **args) {
    char *pwd = getcwd(NULL, 0);
    char *p = NULL;
    int err = 0;

    if (args[1] != NULL && args[1][0] == '-') {
        if (mx_get_char_index(args[1], 'P') > -1) {
            write(1, pwd, strlen(pwd));
            write(1, "\n", 1);
            return 0;
        }
    }
    p = getenv("PWD");
    if (mx_opencheck(getenv("PWD"), &err, 0))
        write(1, p, strlen(p));
    else 
        write(1, pwd, strlen(pwd));
    write(1, "\n", 1);
    free(pwd);
    return 0;
}