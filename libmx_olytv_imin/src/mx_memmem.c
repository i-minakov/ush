#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len){
if (big_len <= 0 || little_len <= 0) return NULL;
unsigned char *b = (unsigned char *) big;
unsigned char *l = (unsigned char *) little;
  
unsigned long schet = 0;
unsigned long i = 0;

  for ( ; i < big_len; i++) {
    schet = 0;
    for (unsigned long y = 0; y < little_len ; y++) {
      if (b[i + y] == l[y]) schet++;
      if(schet == little_len) {
        for (unsigned long j = 0; j < i; j++) b++;
        return (char *) b;
      }
    }
  }
    return NULL;
}
