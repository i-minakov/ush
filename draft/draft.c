#include "../inc/parse.h"

void get_format_str(char *s, t_frmt_lst **arr) {
}

void do_nothing(int sig) {
}

// void () {
// }

int process_output(char **args, t_list *pids) {
    pid_t pid;
    pid_t wait;
    int bins = 0;
    int status;
    int stop = 0;
    int p[2];

    signal(SIGTSTP, do_nothing);
    pipe(p);
    if ((pid = fork()) == -1) {
        perror("fork");
        return -1;
    }
    if (pid == 0) {
        close(p[0]);
        dup2(p[1], 1);
        close(p[1]);
        // exec "who";
        bins = execvp(*args, args);
    }
    else
        for (wait = waitpid(pid, &status, WUNTRACED);
             !WIFEXITED(status) && !WIFSIGNALED(status);
             wait = waitpid(pid, &status, WUNTRACED)) {
            if (WIFSTOPPED(status))
                break;
        }
    errno = 0;
    return bins;
}


char *subshell_substitution(char *s) {

}

// char *str_replace(char *orig, int start, int end, char *sub) {
// //     char *new;

// //     if (!sub || !orig)
// //         return NULL;
// //     if (end - start + 1 < strlen(sub))

    
// //     memmove(orig + start + strlen(sub), orig + end + 1,
// //             strlen(orig + end + 1) + 1);
// }


// bool isquote(char c) {
//     return c == '\"' || c == '\'' || c == '\`';
// }

// int find_quote(char *s, int start) {
//     if (!s)
//         return -2;
//     for (int i = start; s[i]; i++)
//         if (isquote(s[i]))
//             return i;
//     return -1;
// }

// int find_doubquote_pair(char *s, char *q, int start) {
//     if (!s)
//         return -2;
//     for (int i = start; s[i]; i++)
//         if (s[i] == q && s[i - 1] != '\\')
//             return i;
//     return -1;
// }

// t_qts_params *new_quote_range(int start, int end, char quote) {
//     t_qts_params *p = malloc(sizeof(t_qts_params));

//     if (!p) {
//         perror(strerror(errno));
//         return NULL;
//     }
//     p->type = quote;
//     p->range[0] = start;
//     p->range[1] = end;
//     return p;
// }

// int set_quotes_ranges(char *s, t_list **list) {
//     int open_q_ind;
//     int close_q_ind;

//     if (!list || !s || (open_q_ind = find_quote(s, 0)) < 0)
//         return 0;
//     if ((close_q_ind = find_dbl_quote_pair(s, s[open_q_ind], open_q_ind + 1) < 0))
//         return -1;
//     mx_push_front(list, new_quote_range(open_q_ind, close_q_ind,
//                                         s[open_q_ind]));
//     if (s[open_q_ind] == '\`')
//         str_replace(s, open_q_ind, close_q_ind, subshel_substitution());

// }

