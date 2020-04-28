#include "libmx.h"

char *mx_strcpy(char *dst, const char *src)
{
        int len = 0;
    while(src[len]){
        len++;
    }
    for (int i = 0; i<=len; i++){
        dst[i] = src[i];
    }  
    return dst;
    // int i = 0;
    // for (; src[i]; i++) 
    //     dst[i] = src[i];
    // i++;
    // dst[i] = '\0';
    // return dst;
}
