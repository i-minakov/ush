#include "../../inc/ush.h"

t_range *is_inside_of(int i, enum e_quote type, t_frmt_lst **arr) {
    for (t_frmt_lst *p = arr[type]; p; p = p->next)
        if (i >= p->data->start && i <= p->data->end)
            return p->data;
    return NULL;
}

void mark_slash_semicolon_dbl_single_quote(char *s, t_frmt_lst **arr) {
    for (t_frmt_lst *p = arr[SLASH]; p; p = p->next)
        if (!p->data->start && !is_inside_of(p->data->end, DOL_CMD, arr))
            s[p->data->end] = M_SKP;
    for (t_frmt_lst *p = arr[SEMICOL]; p; p = p->next)
        if (!is_inside_of(p->data->end, DOL_CMD, arr))
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

void mx_mark_chars(char *s, t_frmt_lst **arr) {

}
