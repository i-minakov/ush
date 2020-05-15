#include "libmx.h"


t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *))
{
    if (lst == NULL) return NULL;
    int f = 1;
    while (f) {
        f = 0;
        for (t_list *t = lst; t->next; t = t->next){
            if (cmp(t->data, t->next->data)) {
                t_list *m = t->data;
                t->data = t->next->data;
                t->next->data = m;
                f = 1;
            }
        }
    }
    return lst;
}

