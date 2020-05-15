#include "libmx.h"

void mx_push_front(t_list **list, void *data)
{ 
    t_list *p = *list;
    t_list *t = mx_create_node(data);
    t->next = p;
    *list = t;
}
