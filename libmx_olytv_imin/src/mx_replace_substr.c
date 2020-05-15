#include "libmx.h"

// char* mx_replace_substr(const char* str, const char* sub, const char* replace)
// {
//   if (str == 0 || sub == 0 || replace == 0) return 0;
//   int len = mx_strlen(str) - mx_strlen(sub) + mx_strlen(replace);
//   char* res = mx_strnew(len);
//   int l = 0;
//   for (int i = 0, j = 0; str[i]; i++) {
//     for (int t = 0; sub[t]; t++) if (str[i + t] == sub[t]) l++;
//     if (l == mx_strlen(sub)) {
//       for (int k = 0; replace[k]; j++, k++) res[j] = replace[k];
//       i = i + mx_strlen(sub) - 1;
//     }
//     else {res[j] = str[i]; j++;}
//     l = 0;
//   }
//   return res;
// }

char *mx_replace_substr(char *str, const char *sub, const char *replace) {
    if (!sub || !str || !replace || !mx_strlen(str)) 
        return NULL;

    if (!mx_strlen(sub) || !mx_strlen(replace) || 
            mx_count_substr(str, sub) < 0) 
        return (char *) str;
    
    char *rez = mx_strnew(mx_strlen(str) + mx_count_substr(str, sub) 
        * (mx_strlen(replace) - mx_strlen(sub)));
    for (int i = 0, k = 0; i < mx_strlen(str); i++) {
        if (!mx_get_substr_index(&str[i], sub)) {
            for (int j = 0; j < mx_strlen(replace); j++, k++) 
                rez[k] = replace[j];
            i += mx_strlen(sub) - 1;
        } else 
            rez[k] = str[i], k++;
    }
    free(str);
    return rez;
}

