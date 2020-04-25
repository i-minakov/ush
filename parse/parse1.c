#include "../inc/ush.h"

// t_frmt_lst *arr[NUM_Q] = {NULL};

void mx_pop_format(t_frmt_lst **del) {
    free((*del)->data);
    mx_pop_front((t_list **)del);
}

void mx_push_format(t_frmt_lst **add, int start, int end, t_frmt_lst **del) {
    mx_push_front((t_list **)add, malloc(sizeof(t_qts_params)));
    (*add)->data->start = start;
    (*add)->data->end = end;
    if (del)
        mx_pop_format(del);
}


int find_sin_q_pair(char *s, int *i, t_frmt_lst **arr) {
    for (int start = (*i)++; s[*i]; (*i)++) {
        if (s[*i] == '\'')  {
            mx_push_format(arr + SIN_Q, start, *i, NULL);
            return 0;
        }
    }
    fprintf(stderr, MX_ERR_PARSE_CLSSINQ);
    return -1;
}

int find_brace_pair(char *s, int *i, t_frmt_lst **arr) {
    int start = *i;

    *i += 2;
    for (; s[*i]; (*i)++) {
        if (isalpha(s[*i]) || isdigit(s[*i]))
            continue;
        else if (s[*i] == '\}') {
            mx_push_format(arr + DOL_BP, start, *i, NULL);
            return 0;
        }
        else {
            fprintf(stderr, MX_ERR_PARSE_BADSBN);
            break;
        }
    }
    fprintf(stderr, MX_ERR_PARSE_CLSBRC);
    return -1;
}

int find_dollar_param_end(char *s, int *i, t_frmt_lst **arr) {
    int start = *i;

    if (s[*i + 1] == '?') {
        mx_push_format(arr + DOL_P, start, *i + 1, NULL);
        return 0;
    }
    while (isalpha(s[*i + 1]) || isdigit(s[*i + 1]))
        (*i)++;
    if (*i - start == 1) {  // unescaped $ with no characters
        fprintf(stderr, MX_ERR_PARSE_UNESCDOL);
        return -1;
    }
    mx_push_format(arr + DOL_P, start, *i, NULL);
    return 0;
}

int check_double_quote(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\"')
        return 1;
    if (arr[TDBL_Q]) {
        if (arr[TDOL_CMD]) {
            if (arr[TDBL_Q]->data->start > arr[TDOL_CMD]->data->start)
                mx_push_format(arr + DBL_Q, arr[TDBL_Q]->data->start, *i,
                               arr + TDBL_Q);
            else
                mx_push_format(arr + TDBL_Q, *i, -1, NULL);
        }
        else
            mx_push_format(arr + DBL_Q, arr[TDBL_Q]->data->start, *i,
                           arr + TDBL_Q);
    }
    else
        mx_push_format(arr + TDBL_Q, *i, -1, NULL);
    return 0;
}

int check_single_quote(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\'')
        return 1;
    if (arr[TDOL_CMD] && (!arr[TDBL_Q] || (arr[TDBL_Q]
        && arr[TDBL_Q]->data->start < arr[TDOL_CMD]->data->start))) {
        find_sin_q_pair(s, i, arr);  // changes position
    }
    return 0;
}

int check_dollar(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\$')
        return 1;
    if (s[*i + 1] == '\(') {
        mx_push_format(arr + TDOL_CMD, *i, -1, NULL);
        (*i)++;
        return 0;
    }
    else if (s[*i + 1] == '\{')
        return find_brace_pair(s, i, arr);  // changes position
    else
        return find_dollar_param_end(s, i, arr);  // changes position
}

int check_backquote(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\`')
        return 1;
    mx_push_format(arr + TBCK_Q, *i, -1, NULL);
    return 0;
}

int check_open_paren(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\(')
        return 1;
    fprintf(stderr, MX_ERR_PARSE_UNESCOPPAR);
    return -1;
}

int check_close_paren(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\)')
        return 1;
    if (arr[TDOL_CMD]) {
        mx_push_format(arr + DOL_CMD, arr[TDOL_CMD]->data->start, *i,
                       arr + TDOL_CMD);
        return 0;
    }
    else {
        fprintf(stderr, MX_ERR_PARSE_UNESCCLPAR);
        return -1;
    }
}

int check_open_brace(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\{')
        return 1;
    fprintf(stderr, MX_ERR_PARSE_UNESCOPBRC);
    return -1;
}

int check_close_brace(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\}')
        return 1;
    fprintf(stderr, MX_ERR_PARSE_UNESCCLBRC);
    return -1;
}

int check_slash(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\\')
        return 1;
    if (arr[TDBL_Q]) {
        if (((arr[TDOL_CMD]
            && arr[TDBL_Q]->data->start > arr[TDOL_CMD]->data->start)
            || !arr[TDOL_CMD])
            && mx_get_char_index("\`\$\"\\", s[*i + 1]) >= 0) {
            mx_push_format(arr + TSLASH, *i, -1, NULL);
        }
    }
    else if (mx_get_char_index(MX_SLASH_SPEC, s[*i + 1]) >= 0)
        mx_push_format(arr + TSLASH, *i, -1, NULL);
    return 0;
}

int check_semicolon(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\;')
        return 1;
    if (arr[TDBL_Q] && ((arr[TDOL_CMD]
        && arr[TDBL_Q]->data->start > arr[TDOL_CMD]->data->start)
        || !arr[TDOL_CMD])) {
        return 0;
    }
    mx_push_format(arr + SEMICOL, *i, -1, NULL);
    return 0;
}

int mx_get_format_str(char *s, t_frmt_lst **arr) {
    int (*fptr[10])(char *, int *, t_frmt_lst **) = {check_double_quote,
    check_single_quote, check_dollar, check_backquote, check_open_paren,
    check_close_paren, check_open_brace, check_close_brace,
    check_slash, check_semicolon};
    int func_num;

    for (int i = 0; s[i]; i++) {
        if (arr[TSLASH]) {
            mx_pop_format(arr + TSLASH);
            continue;
        }
        if ((func_num = mx_get_char_index(MX_FUNC_SYMBOLS, s[i])) < 0)
            continue;
        if (fptr[func_num](s, &i, arr) < 0)
            return -1;
    }
    if (arr[TDBL_Q] || arr[TBCK_Q] || arr[TDOL_CMD])
        return -1;
    return 0;
}









