#include "libmx.h"

void mx_pop_back(t_list **head)
{
    if (head == 0 || *head == NULL) return ;
    t_list *p = *head;
    while (p->next->next == NULL) p = p->next;
    free(p->next->next);
    p->next->next = NULL;
}
