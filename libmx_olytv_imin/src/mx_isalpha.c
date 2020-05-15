#include "libmx.h"

bool mx_isalpha(char c) {
 if ((c > 96 && c < 123) || (c > 64 && c < 91)) 
    return true;
 return false;
}
