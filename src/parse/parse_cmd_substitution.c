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

static bool is_outer_dblq(int start, t_frmt_lst **arr) {
    t_frmt_lst *p;

    for (p = arr[DOL_CMD]; p; p = p->next)
        if (start > p->data->start && start < p->data->end)
            return false;
    for (p = arr[DBL_Q]; p; p = p->next)
        if (start > p->data->start && start < p->data->end)
            return false;
    return true;
}

void create_outer_cmd_subst_dblq_list(t_frmt_lst **arr) {
    t_frmt_lst *list_cmd = NULL;
    t_frmt_lst *list_dblq = NULL;
    t_frmt_lst *p;

    for (p = arr[BCK_Q]; p; p = p->next)
        if (is_outer_cmd_subst(p->data->start, arr))
            mx_push_format(&list_cmd, p->data->start, p->data->end, NULL);
    for (p = arr[DOL_CMD]; p; p = p->next)
        if (is_outer_cmd_subst(p->data->start, arr))
            mx_push_format(&list_cmd, p->data->start, p->data->end, NULL);
    for (p = arr[DBL_Q]; p; p = p->next)
        if (is_outer_dblq(p->data->start, arr))
            mx_push_format(&list_dblq, p->data->start, p->data->end, NULL);
    // mx_free_format_lists(arr);
    arr[OUT_CMDS] = list_cmd;
    arr[OUT_DBQ] = list_dblq;
}

static void paste_cmd_subst(char **str, char *replace, t_range *rep_range,
                            t_frmt_lst **arr) {
    int shift = strlen(replace) - (rep_range->end - rep_range->start + 1);

    for (t_frmt_lst *p = arr[OUT_CMDS]; p; p = p->next) {
        if (p->data->start > rep_range->start) {
            p->data->start += shift;
            p->data->end += shift;
        }
    }
    for (t_frmt_lst *dblq_p = arr[OUT_DBQ]; dblq_p; dblq_p = dblq_p->next) {
        if (dblq_p->data->start > rep_range->start) {
            dblq_p->data->start += shift;
            dblq_p->data->end += shift;
        }
        else if (dblq_p->data->end > rep_range->end)
            dblq_p->data->end += shift;
    }
    mx_replace_sub_str(str, rep_range->start, rep_range->end, replace);
    free(replace);
}

static void unslash_str(char **str) {
    int new_p = 0;
    char *new = calloc(1, strlen(*str) + 1);
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

static void mark_cmd_sbst_output() {
    
}

int mx_cmd_substitution(char **str, t_frmt_lst **arr) {
    t_frmt_lst *list;
    char *replace;
    int start_pos;

    // if (!arr[BCK_Q] && !arr[DOL_CMD])
    //     return 0;
    create_outer_cmd_subst_dblq_list(arr);
    while (list) {
        start_pos = (*str)[list->data->start] == '`' ? list->data->start + 1
                                                     : list->data->start + 2;
        replace = strndup(*str + start_pos, list->data->end - start_pos);
        if ((*str)[list->data->start] == '`') {
            unslash_str(&replace);
        }

    }
    // for ()
}
