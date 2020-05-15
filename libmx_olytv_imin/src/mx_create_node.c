#include "libmx.h"

t_list *mx_create_node(void *data)
{
    t_list *t = (t_list *)malloc(sizeof(t_list) * 1);
    t->data = data;
    t->next = NULL;
    return t;
}
