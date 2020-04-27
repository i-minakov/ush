#include "../../inc/ush.h"

// static char **check(char *line) {
//     char **res = NULL;    
//     char *tmp = NULL;

//     if (mx_get_char_index(line, '\\') == -1)
//         return mx_strsplit(line, ' ');
//     for (int i = 0; line[i]; i++) {
        
//     }
//     free(line);
//     res = mx_strsplit(tmp, '*');
//     for (int i = 0; res[i]; i++)
//         printf("%s\n", res[i]);
//     return res;
// }

// t_frmt_lst *arr[NUM_Q] = {NULL};

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

int check_open_paren(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '(')
        return 1;
    if (arr[TDBL_Q])
        return 0;
    fprintf(stderr, MX_ERR_PARSE_UNESCOPPAR);
    return -1;
    arr++;
}

int check_close_paren(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != ')')
        return 1;
    if (arr[TDOL_CMD] && (!arr[TDBL_Q] || (arr[TDBL_Q]
        && arr[TDBL_Q]->data->start < arr[TDOL_CMD]->data->start))) {
        mx_push_format(arr + DOL_CMD, arr[TDOL_CMD]->data->start, *i,
                       arr + TDOL_CMD);
        return 0;
    }
    else if (arr[TDBL_Q])
        return 0;
    else {
        fprintf(stderr, MX_ERR_PARSE_UNESCCLPAR);
        return -1;
    }
}

int check_open_brace(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '{')
        return 1;
    if (arr[TDBL_Q])
        return 0;
    fprintf(stderr, MX_ERR_PARSE_UNESCOPBRC);
    return -1;
    arr++;  // to trick compiler
}

int check_close_brace(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != '}')
        return 1;
    if (arr[TDBL_Q])
        return 0;
    fprintf(stderr, MX_ERR_PARSE_UNESCCLBRC);
    return -1;
    arr++;  // to trick compiler
}
// echo 123"$(dfjh(f))"

int check_semicolon(char *s, int *i, t_frmt_lst **arr) {
    if (s[*i] != ';')
        return 1;
    if (arr[TDBL_Q] && ((arr[TDOL_CMD]
        && arr[TDBL_Q]->data->start > arr[TDOL_CMD]->data->start)
        || !arr[TDOL_CMD])) {
        return 0;
    }
    mx_push_format(arr + SEMICOL, *i, -1, NULL);
    return 0;
}

int check_slash(char *s, int *i, t_frmt_lst **arr) {
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
            || !arr[TDBL_Q] ? false : true, -1, NULL);
    return 0;
}

int mx_get_format_str(char *s, t_frmt_lst **arr) {
    int (*fptr[10])(char *, int *, t_frmt_lst **) = {check_double_quote,
    mx_check_single_quote, mx_check_dollar, mx_check_backquote, check_open_paren,
    check_close_paren, check_open_brace, check_close_brace,
    check_slash, check_semicolon};
    int func_num;
// dflkl "sdf}ddf
    for (int i = 0; s[i]; i++) {
        if (arr[TSLASH]) {
            if (s[i] == '\\')
                mx_push_back_format(arr + SLASH, true, -1, NULL);
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


void parse(char *line, t_ush *ush, t_jobs **jobs) {
    ush++;
    jobs++;
    t_frmt_lst *arr[NUM_Q] = {0};
    char *names[] = {
        "SIN_Q",
        "DBL_Q",
        "TDBL_Q",  //temporary opened stack flag
        "BCK_Q",
        "TBCK_Q",  //temporary opened stack flag
        "DOL_CMD",
        "TDOL_CMD",  //temporary opened stack flag
        "DOL_BP",
        "DOL_P",
        "SLASH",
        "TSLASH",  //temporary opened stack flag
        "SEMICOL",
        NULL
    };

    printf("s = <%s>, len = %lu\n" , line, strlen(line) );
    if (mx_get_format_str(line, arr) < 0)
            return;
    for (int i = 0; i < NUM_Q; i++) {
        if (!arr[i])
            continue;
        if (i == SLASH) {
            for(t_frmt_lst *p = arr[i]; p; p = p->next) {
                printf(p->data->start? "1" : "0");
            }
            printf("\n");
            continue;
        }
        printf("%d. %s:\n\n", i, names[i]);
        for(t_frmt_lst *p = arr[i]; p; p = p->next) {
            printf("%s\n", strndup(line + p->data->start,
                   p->data->end - p->data->start + 1));
        }
        printf("\n");
    }

    // char *res = NULL;
    // char **m = NULL;

    // char **q = NULL;

    // res = mx_strtrim(line);
    // mx_strdel(&line);

    // q = mx_strsplit(res, ';');
    // for (int i = 0; q[i]; i++) {
    //     m = check(q[i]);
    //     ush->last_return = detect_builds(m, ush, jobs); 
    //     mx_del_strarr(&m);
    // }
    // mx_del_strarr(&q);
    // free(res);

}
