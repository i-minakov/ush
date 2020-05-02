#include "../../inc/ush.h"

static void do_nothing(int sig) {
}

static char *read_output(int fd, pid_t pid) {
    int read_bytes;
    char *buf = calloc(1, BUFSIZ);
    char *buf_p = buf;
    int size = BUFSIZ;
    int status;

    waitpid(pid, &status, WUNTRACED);
    if (WIFEXITED(status)) {
        free(buf);
        return NULL;
    }
    for ((read_bytes = read(fd, buf_p, BUFSIZ)); read_bytes == BUFSIZ;
        read_bytes = read(fd, buf_p, BUFSIZ)) {
            if (read_bytes == -1) {
                free(buf);
                return NULL;
            }
        buf = reallocf(buf, (size += BUFSIZ));
        buf_p = buf + size - BUFSIZ;
    }
    errno = 0;
    return buf;
}

char *mx_process_output(char *str, int (*parse_p)(char *, t_ush *, t_jobs **),
                        t_ush *ush, t_jobs **jobs) {
    pid_t pid;
    int p[2];  // pipe

    signal(SIGTSTP, do_nothing);
    pipe(p);
    if ((pid = fork()) == -1) {
        perror("fork");
        return NULL;
    }
    if (pid == 0) {
        close(p[0]);
        dup2(p[1], 1);
        close(p[1]);
        if (parse_p(str, ush, jobs) == -1) {
            fprintf(stderr, MX_ERR_PARSE_CMDSBN);
            exit(1);
        }
        exit(0);
    }
    return read_output(p[0], pid);
}
