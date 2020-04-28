#include "libmx.h"

void mx_pop_front(t_list **head)
{
    if (head == 0 || *head == NULL) return ;
    t_list *p = *head;
    t_list *t = p->next;
    free(*head);
    *head = NULL;
    *head = t;
}


