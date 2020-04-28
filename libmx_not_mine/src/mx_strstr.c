#include "libmx.h"

char *mx_strstr(const char *haystack, const char *needle)
{
    if (mx_strlen(haystack) < mx_strlen(needle)) return NULL;
    if (haystack == NULL) return NULL;
    if (!mx_strlen(needle)) return (char *)haystack;
    int k = 0, res = 0;
    for (int i = 0; haystack[i]; i++)
    {   
        for (int j = 0; needle[j]; j++) if (needle[j] == haystack[i + j]) k++;
        if (k == mx_strlen(needle)) { res = i; break;}
        k = 0;
    }
    if (k == mx_strlen(needle)) {
        for (int i = 0; i < res; i++, haystack++);
        return (char *)haystack;
    }
    else return NULL;
}
