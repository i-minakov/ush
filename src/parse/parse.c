#include "../../inc/ush.h"

static int check_semicolon(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != ';')
        return 1;
    if (arr[TDBL_Q] && ((arr[TDOL_CMD]
        && arr[TDBL_Q]->data->start > arr[TDOL_CMD]->data->start)
        || !arr[TDOL_CMD])) {
        return 0;
    }
    mx_push_format(arr + SEMICOL, *i, *i, NULL);
    return 0;
}

static int check_slash(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '\\')
        return 1;
    if (arr[TDBL_Q]) {
        if (((arr[TDOL_CMD]
            && arr[TDBL_Q]->data->start > arr[TDOL_CMD]->data->start)
            || !arr[TDOL_CMD])
            && mx_get_char_index("`$\"\\", s[*i + 1]) >= 0) {
            mx_push_format(arr + TSLASH, *i, -1, NULL);
        }
    }
    else if (mx_get_char_index(MX_SLASH_SPEC, s[*i + 1]) >= 0)
        mx_push_format(arr + TSLASH, *i, -1, NULL);
    if (!arr[TDOL_CMD])
        mx_push_back_format(arr + SLASH,
            (arr[TDBL_Q] && mx_get_char_index("`$\"\\", s[*i + 1]) >= 0)
            || !arr[TDBL_Q] ? false : true, *i, NULL);
    return 0;
}

int mx_get_format_str(char *s, t_frmt_lst **arr) {
    int (*fptr[10])(char *, int *, t_frmt_lst **) = {mx_check_double_quote,
    mx_check_single_quote, mx_check_dollar, mx_check_backquote, mx_check_open_paren,
    mx_check_close_paren, mx_check_open_brace, mx_check_close_brace,
    check_slash, check_semicolon};
    int func_num;

    for (int i = 0; s[i]; i++) {
        if (arr[TSLASH]) {
            if (s[i] == '\\')
                mx_push_back_format(arr + SLASH, true, i, NULL);
            mx_pop_format(arr + TSLASH);
            continue;
        }
        if ((func_num = mx_get_char_index(MX_FUNC_SYMBOLS, s[i])) < 0)
            continue;
        if (fptr[func_num](s, &i, arr) < 0)
            return -1;
    }
    if (arr[TDBL_Q] || arr[TDOL_CMD]) {
        fprintf(stderr, MX_ERR_PARSE_UNMATCH "%s", arr[TDBL_Q] ? "\"\n"
                                                               : "$(\n");
        return -1;
    }
    return 0;
}

static void quit_parse(char *line, t_ush *ush, int ret_val, 
                       t_frmt_lst **arr ) {
    mx_free_format_lists(arr);
    if (line)
        free(line);
    if (ret_val >= 0)
        ush->last_return = ret_val;
}

int parse_exec_command(char *subline, t_ush *ush) {
    t_frmt_lst *arr[NUM_Q] = {NULL};
    char **argv;

    mx_get_format_str(subline, arr);
    mx_mark_slash_dbl_single_quote(subline, arr);
    mx_mark_chars(subline, arr);

    if (mx_handle_substitutions(&subline, arr, ush) == -1) {  // parse errors
        quit_parse(NULL, ush, 1, arr);
        return -1;
    }
    subline = mx_clear_str(subline);
    argv = mx_strsplit(subline, M_DEL);
    ush->last_return = detect_builds(argv, ush);
    mx_del_strarr(&argv);
    free(subline);
    quit_parse(NULL, ush, -1, arr);
    return 0;
}

int mx_parse(char *line, t_ush *ush) {
    t_frmt_lst *arr[NUM_Q] = {NULL};
    char **subcommands = {NULL};
    int com_count;

    if (mx_get_format_str(line, arr) < 0) {  // parse errors
        quit_parse(line, ush, 1, arr);
        return -1;
    }
    mx_mark_semicolon(line, arr);
    subcommands = mx_strsplit_ncount(line, M_SEMIC, &com_count);
    for (int i = 0; i < com_count; i++)
        parse_exec_command(strdup(subcommands[i]), ush);
    mx_del_strarr(&subcommands);
    quit_parse(line, ush, -1, arr);
    return 0;
}
