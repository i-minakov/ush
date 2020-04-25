#include "../inc/ush.h"

static void uns_var(t_list **env_set, int count, t_list **b) {
    t_list *front = *env_set;
    t_list *back = *b;

    if (count == 0) {
        if (front->next == NULL) {
            free_list2(env_set);
            front = mx_create_node(NULL);
        }
        else
            mx_pop_front(env_set);
        return ;
    }
    for (int i = 0; i < count - 1; i++)
        front = front->next;
    front->next = back->next;
    free(back->data);
    back->data = NULL;
    free(back);
    back = NULL;

}

int ush_unset(char **args, t_list **env_set) {
    char **tmp = NULL;
    char **sub = NULL;
    int count;

    for (int i = 1; args[i]; i++) {
        // if не содержит минуса
        tmp = mx_strsplit(args [i], '=');
        count = 0;
        for (t_list *f = *env_set; f; f = f->next, count++) {
            if (mx_get_substr_index(f->data, tmp[0]) >= 0) {
                sub =  mx_strsplit(f->data, '=');
                if (mx_strcmp(sub[0], tmp[0]) == 0) {
                    uns_var(env_set, count, &f);
                    unsetenv(tmp[0]);
                }
                mx_del_strarr(&sub);
            } 
        }
        mx_del_strarr(&tmp);
    }
    //что происходит если вписываю а=b
    //если нет такой вар флаг оповещение ерр
    return 1;
}
