#include "../inc/ush.h"

t_jobs *mx_create_job(char **data, int num, pid_t pid)
{
    t_jobs *t = (t_jobs *)malloc(sizeof(t_jobs) * 3);
    t->data = copy_dub_arr(data);
    t->num = num;
    t->pid = pid;
    t->next = NULL;
    return t;
}
