#include "libmx.h"

void mx_del_strarr(char ***arr) {
char **p = *arr;
  for ( int i = 0; p[i]; i++) {
       free(p[i]);
       p[i] = NULL;
  }
   free(p);
   p = NULL;
}
