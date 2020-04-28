#include "../../inc/ush.h"

static void param_dollar_expansion(char **str, t_frmt_lst **arr,
                                   int last_ret_status) {
    char *s;

    for (t_frmt_lst *p = arr[DOL_P]; p; p = arr[DOL_P]) {
        if ((*str)[p->data->start + 1] == '?') {
            s = mx_itoa(last_ret_status);
            mx_replace_sub_str(str, p->data->start, p->data->end, s);
        }
        else {
            s = strndup(*str + p->data->start + 1, p->data->end - p->data->start);
            mx_replace_sub_str(str, p->data->start, p->data->end, getenv(s));
        }
        free(s);
        mx_free_format_lists(arr);
        mx_get_format_str(*str, arr);
    }
}
// sdjfnk $HOME$PWD - segv
static void param_dollar_braces_expansion(char **str, t_frmt_lst **arr,
                                          int last_ret_status) {
    char *s;

    for (t_frmt_lst *p = arr[DOL_BP]; p; p = arr[DOL_BP]) {
        if ((*str)[p->data->start + 2] == '?') {
            s = mx_itoa(last_ret_status);
            mx_replace_sub_str(str, p->data->start, p->data->end, s);
        }
        else {
            s = strndup(*str + p->data->start + 2, p->data->end - p->data->start - 2);
            mx_replace_sub_str(str, p->data->start, p->data->end, getenv(s));
        }
        free(s);
        mx_free_format_lists(arr);
        mx_get_format_str(*str, arr);
    }
}

void mx_param_expansions(char **str, t_frmt_lst **arr, int last_ret_status) {
    char *s;

    if (!str || !arr)
        return;
    param_dollar_expansion(str, arr, last_ret_status);
    param_dollar_braces_expansion(str, arr, last_ret_status);
}
