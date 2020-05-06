// #include "../../inc/ush.h"

// char *tilde2(char *str) {
//     char **m = mx_strsplit(str, '/');

//     if (strcmp(m[0], "~+") == 0) {
//         mx_del_strarr(&m);
//         return mx_replace_substr(str, "~+", getenv("PWD"));
//     }
//     if (strcmp(m[0], "~-") == 0) {
//         mx_del_strarr(&m);
//         return mx_replace_substr(str, "~-", getenv("OLDPWD"));
//     }
//     return NULL;
// }

// char *tilde(char *str) {
//     char *res = NULL;
//     char *tmp = NULL;
//     char **m = NULL;

//     if (mx_get_char_index(str, '~') != 0)
//         return NULL;
//     m = mx_strsplit(str, '/');
//     if (strcmp(m[0], "~+") == 0 || strcmp(m[0], "~-") == 0) {
//         mx_del_strarr(&m);
//         return tilde2(str);
//     }
//     tmp = mx_strjoin("~", getenv("USER"));
//     if (strcmp(m[0], "~") != 0 && strcmp(m[0], tmp) != 0) {
//         mx_del_strarr(&m);
//         free(tmp);
//         return NULL;
//     }
//     res = mx_replace_substr(str, m[0], getenv("HOME"));
//     mx_del_strarr(&m);
//     free(tmp);
//     return res;
// }

// int mx_tilde_expansion(char **argv) {
//     char *tmp = NULL;

//     for (char **s = argv[1]; *s; s++) {
//         if ((tmp = tilde(*s)) == NULL) {
//             return -1;
//         }
//         free(*s);
//         *s = tmp;
//     }
//     return 0;
// }
