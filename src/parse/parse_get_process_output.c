#include "../../inc/ush.h"

static bool check_if_exited(pid_t pid, char *buf) {
    int status;

    waitpid(pid, &status, WUNTRACED);
    if (WIFEXITED(status)) {
        free(buf);
        return 1;
    }
    return 0;
}

static void end_reading(pid_t pid, int *pipe) {
    int status;
    
    close(pipe[0]);
    waitpid(pid, &status, WUNTRACED);
    errno = 0;
}

static char *read_output(pid_t pid, int *pipe) {
    int read_bytes;
    char *buf = calloc(1, BUFSIZ);
    char *buf_p = buf;
    int size = BUFSIZ;

    close(pipe[1]);
    for (read_bytes = read(pipe[0], buf_p, BUFSIZ); read_bytes == BUFSIZ;
        read_bytes = read(pipe[0], buf_p, BUFSIZ)) {
            if (read_bytes == -1) {
                free(buf);
                return NULL;
            }
        buf = reallocf(buf, (size += BUFSIZ));
        buf_p = buf + size - BUFSIZ;
    }
    end_reading(pid, pipe);
    return buf;
}

static char *process_output(char *str, int (*parse_p)(char *, t_ush *),
                            t_ush *ush) {
    pid_t pid;
    int p[2];  // pipe

    signal(SIGTSTP, SIG_IGN);
    pipe(p);
    if ((pid = fork()) == -1) {
        perror("fork");
        return NULL;
    }
    if (pid == 0) {
        close(p[0]);
        dup2(p[1], 1);
        close(p[1]);
        if (parse_p(str, ush) == -1) {
            fprintf(stderr, MX_ERR_PARSE_CMDSBN);
            exit(1);
        }
        exit(0);
    }
    return read_output(pid, p);
}

char *mx_get_subst_outputs(char *str, int (*parse_p)(char *, t_ush *),
                           t_ush *ush) {
    char **subcommands = {NULL};
    char *sum_output = NULL;

    if (mx_semicolon_split(str, ush, &subcommands) == -1) {  // parse errors
        mx_quit_parse(str, ush, 1, NULL);
        return NULL;
    }
    for (char **s = subcommands; *s; s++) {
        sum_output = mx_cooljoin(sum_output, process_output(*s,
                                 mx_parse_exec, ush));
    }
    mx_del_strarr(&subcommands);
    mx_quit_parse(NULL, ush, -1, NULL);
    return sum_output;
}

