#include "libmx.h"

int mx_list_size(t_list *list)
{
    int sum = 0;
    t_list *p = list;
    if (!p) return 0;
    for ( t_list *i = p; i; i = i->next) sum++;
    return sum;
}

