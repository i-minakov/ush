#include "../../inc/ush.h"

t_range *mx_is_inside_of(int i, enum e_quote type, t_frmt_lst **arr) {
    for (t_frmt_lst *p = arr[type]; p; p = p->next)
        if (i >= p->data->start && i <= p->data->end)
            return p->data;
    return NULL;
}

void mx_mark_slash_semicolon_dbl_single_quote(char *s, t_frmt_lst **arr) {
    for (t_frmt_lst *p = arr[SLASH]; p; p = p->next)
        if (!p->data->start && !mx_is_inside_of(p->data->end, DOL_CMD, arr))
            s[p->data->end] = M_SKSL;
    for (t_frmt_lst *p = arr[SEMICOL]; p; p = p->next)
        if (!mx_is_inside_of(p->data->start, DOL_CMD, arr))
            s[p->data->end] = M_SEMIC;
    for (t_frmt_lst *p = arr[DBL_Q]; p; p = p->next)
        if (!mx_is_inside_of(p->data->start, DOL_CMD, arr)) {
            s[p->data->start] = M_SKP;
            s[p->data->end] = M_SKP;
        }
    for (t_frmt_lst *p = arr[SIN_Q]; p; p = p->next) {
            s[p->data->start] = M_SKP;
            s[p->data->end] = M_SKP;
    }
}

char *mx_clear_str(char *str) {  // !!!
    int new_p = 0;
    char *new = calloc(1, strlen(str) + 1);

    for (char *s = str; *s; s++) {
        if (*s == M_SKP)
            continue;
        new[new_p++] = *s;
    }
    free(str);
    return new;
}

void mx_break_words_exec(char *s, t_frmt_lst **arr, t_ush *ush) {
    int com_count;
    char **commands;
    char ***args;

    s = mx_clear_str(s);
    commands = mx_strsplit_ncount(s, M_SEMIC, &com_count);
    args = calloc(com_count + 1, sizeof(char **));
    for (int i = 0; i < com_count; i++)
        ush->last_return = detect_builds(
            (args[i] = mx_strsplit(commands[i], M_DEL)), ush);
    mx_del_strarr(&commands);

    for (int i = 0; args[i]; i++)
        mx_del_strarr(args + i);
    free(args);
    free(s);
}
