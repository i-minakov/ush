#include "../../inc/ush.h"


static bool is_outer_cmd_subst(int start, t_frmt_lst **arr) {
    t_frmt_lst *p;

    for (p = arr[BCK_Q]; p; p = p->next)
        if (start > p->data->start && start < p->data->end)
            return false;
    for (p = arr[DOL_CMD]; p; p = p->next)
        if (start > p->data->start && start < p->data->end)
            return false;
    return true;
}

static t_frmt_lst *create_outer_cmd_subst_list(t_frmt_lst **arr) {
    t_frmt_lst *list = NULL;
    t_frmt_lst *p;

    for (p = arr[BCK_Q]; p; p = p->next)
        if (is_outer_cmd_subst(p->data->start, arr))
            mx_push_format(&list, p->data->start, p->data->end, NULL);
    for (p = arr[DOL_CMD]; p; p = p->next)
        if (is_outer_cmd_subst(p->data->start, arr))
            mx_push_format(&list, p->data->start, p->data->end, NULL);
    mx_free_format_lists(arr);
    return list;
}

static void paste_cmd_subst(char **str, char *replace, t_range *rep_range,
                            t_frmt_lst *list) {
    int shift = strlen(replace) - (rep_range->end - rep_range->start + 1);

    for (t_frmt_lst *p = list; p; p = p->next) {
        if (p->data->start > rep_range->start) {
            p->data->start += shift;
            p->data->end += shift;
        }
    }
    mx_replace_sub_str(str, rep_range->start, rep_range->end, replace);
    free(replace);
}

static void unslash_str(char **str) {
    int new_p = 0;
    char *new = calloc(1, strlen(*str + 1));
    bool flag = 0;

    for (char *s = *str; *s; s++) {
        if (*s == '\\') {
            if (flag)
                continue;
            else
                flag = 1;
        }
        new[new_p++] = *s;
    }
    free(*str);
    *str = new;
}

int mx_cmd_substitution(char **str, t_frmt_lst **arr) {
    if (!arr[BCK_Q] && !arr[DOL_CMD])
        return 0;

    // for ()
}
