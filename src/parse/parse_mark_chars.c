#include "../../inc/ush.h"

static t_range *is_inside_of(int i, enum e_quote type, t_frmt_lst **arr) {
    for (t_frmt_lst *p = arr[type]; p; p = p->next)
        if (i >= p->data->start && i <= p->data->end)
            return p->data;
    return NULL;
}

static void mark_slash_semicolon_dbl_single_quote(char *s, t_frmt_lst **arr) {
    for (t_frmt_lst *p = arr[SLASH]; p; p = p->next)
        if (!p->data->start && !is_inside_of(p->data->end, DOL_CMD, arr))
            s[p->data->end] = M_SKSL;
    for (t_frmt_lst *p = arr[SEMICOL]; p; p = p->next)
        if (!is_inside_of(p->data->start, DOL_CMD, arr))
            s[p->data->end] = M_SEMIC;
    for (t_frmt_lst *p = arr[DBL_Q]; p; p = p->next)
        if (!is_inside_of(p->data->start, DOL_CMD, arr)) {
            s[p->data->start] = M_SKP;
            s[p->data->end] = M_SKP;
        }
    for (t_frmt_lst *p = arr[SIN_Q]; p; p = p->next) {
            s[p->data->start] = M_SKP;
            s[p->data->end] = M_SKP;
    }
}

static void mx_mark_chars(char *s, t_frmt_lst **arr) {
    t_range *range = NULL;

    for (int i = 0; s[i]; i++) {
        if ((range = is_inside_of(i, DOL_CMD, arr))
            || (range = is_inside_of(i, SIN_Q, arr))
            || (range = is_inside_of(i, BCK_Q, arr)))
            i = range->end;
        else if (MX_IS_SP_TAB_NL(s[i]) && !is_inside_of(i, DBL_Q, arr)
                 && (!i || s[i - 1] != M_SKSL))
            s[i] = M_DEL;
    }
    while((s = strchr(s, M_SKSL)))
        *s = M_SKP;

}

void clear_str(char **str) {
    char *s = *str;
    int old_p = 0;
    int new_p = 0;
    char *new = calloc(1, strlen(s) + 1);

    for (; *s; s++) {
        if (*s == M_SKP)
            continue;
        new[new_p++] = s[old_p];
    }
    mx_strdel(str);
    *str = new;
}

void mx_break_words_exec(char **s, t_frmt_lst **arr, t_ush *ush, t_jobs **jobs) {
    int com_count;
    char **commands;
    char ***args;

    mark_slash_semicolon_dbl_single_quote(*s, arr);
    mx_mark_chars(*s, arr);
    clear_str(s);
    commands = mx_strsplit_ncount(*s, M_SEMIC, &com_count);
    args = calloc(com_count + 1, sizeof(char **));
    for (int i = 0; i < com_count; i++)
        ush->last_return = detect_builds(
            (args[i] = mx_strsplit(commands[i], M_DEL)), ush, jobs);
}
