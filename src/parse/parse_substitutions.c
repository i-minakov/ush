#include "../../inc/ush.h"

// static bool is_outer_cmd_subst(int start, t_frmt_lst **arr) {
//     t_frmt_lst *p;

//     // for (p = arr[BCK_Q]; p; p = p->next)
//     //     if (start > p->data->start && start < p->data->end)
//     //         return false;
//     for (p = arr[DOL_CMD]; p; p = p->next)
//         if (start > p->data->start && start < p->data->end)
//             return false;
//     return true;
// }


// void create_outer_cmd_subst_dblq_list(t_frmt_lst **arr) {
//     t_frmt_lst *list_cmd = NULL;
//     t_frmt_lst *list_dblq = NULL;
//     t_frmt_lst *p;

//     for (p = arr[BCK_Q]; p; p = p->next)
//         if (is_outer_cmd_subst(p->data->start, arr))
//             mx_push_format(&list_cmd, p->data->start, p->data->end, NULL);
//     for (p = arr[DOL_CMD]; p; p = p->next)
//         if (is_outer_cmd_subst(p->data->start, arr))
//             mx_push_format(&list_cmd, p->data->start, p->data->end, NULL);
//     for (p = arr[DBL_Q]; p; p = p->next)
//         if (is_outer_dblq(p->data->start, arr))
//             mx_push_format(&list_dblq, p->data->start, p->data->end, NULL);
//     // mx_free_format_lists(arr);
//     arr[OUT_CMDS] = list_cmd;
//     arr[OUT_DBQ] = list_dblq;
// }

static bool is_outer(int start, t_frmt_lst **arr) {
    t_frmt_lst *p;

    for (p = arr[DOL_CMD]; p; p = p->next)
        if (start > p->data->start && start < p->data->end)
            return false;
    return true;
}

static t_range *is_subst(t_frmt_lst **arr, int start, enum e_quote *type) {
    enum e_quote subs[4] = {BCK_Q, DOL_CMD, DOL_P, DOL_BP};

    for (int i = 0; i < 4; i++) {
        for (t_frmt_lst *p = arr[subs[i]]; p; p = p->next)
            if (p->data->start == start) {
                *type = subs[i];
                return p->data;
            }        
    }
    return NULL;
}

static t_range *is_dble_q(t_frmt_lst **arr, int start) {
    for (t_frmt_lst *p = arr[DBL_Q]; p; p = p->next)
        if (start == p->data->start)
            return p->data;
    return NULL;
}

void create_outer_subst_n_dblq_list(char *s, t_frmt_lst **arr) {
    enum e_quote type = 0;
    t_range *range = NULL;

    for (int i = 0; s[i]; i++) {
        if ((s[i] == '$' || s[i] == '`') && (range = is_subst(arr, i, &type))
            && is_outer(i, arr)) {
            mx_push_back_format(arr + OUT_SUB, range->start, range->end, NULL);
            i = range->end;
        }
        else if (s[i] == '\"' && (range = is_dble_q(arr, i))
                 && is_outer(i, arr)) {
            mx_push_back_format(arr + OUT_DBQ, range->start, range->end, NULL);
        }
    }
}

static void paste_subst(char **str, char *replace, t_range *rep_range,
                            t_frmt_lst **arr) {
    int shift = strlen(replace) - (rep_range->end - rep_range->start + 1);

    for (t_frmt_lst *p = arr[OUT_SUB]->next; p; p = p->next) {
        p->data->start += shift;
        p->data->end += shift;
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

static char *mark_sbst_output(char *str, bool in_quotes) {
    char *s;

    if (!str || !*str)
        return str;
    for (s = str + strlen(str) - 1; *s == '\n'; s--)
        *s = M_SKP;
    if (in_quotes)
        return str;

    for (s = str; *s && *s != M_SKP; s++) {
        if (MX_IS_SP_TAB_NL(*s))
            *s = M_DEL;
    }
    return str;
}


int mx_handle_substitutions(char **str, t_frmt_lst **arr, t_ush *ush) {
    char *replace = NULL;
    char *process_out = NULL;

    create_outer_subst_n_dblq_list(*str, arr);
    for (t_frmt_lst *lst; (lst = arr[OUT_SUB]); mx_pop_format(arr + OUT_SUB)) {
        replace = mx_get_subst_replace_str(str, lst, ush);
        if ((*str)[lst->data->start] == '`'
            || (*str)[lst->data->start + 1] == '(') {
            process_out = mx_process_output(replace, mx_parse, ush);
            free(replace);
            if (!process_out)
                return -1;
            replace = mark_sbst_output(process_out,
                mx_is_inside_of(lst->data->start, OUT_DBQ, arr) ? 1 : 0);
        }
        paste_subst(str, replace, lst->data, arr);  // replace freed
    }
    return 0;
}
