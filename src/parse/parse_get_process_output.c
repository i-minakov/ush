#include "../../inc/ush.h"

static void do_nothing(int sig) {
}

static char *read_output(int fd) {
    int read_bytes;
    char *buf = calloc(1, BUFSIZ);
    char *buf_p = buf;
    int size = BUFSIZ;

    for ((read_bytes = read(fd, buf_p, BUFSIZ)); read_bytes == BUFSIZ;
        read_bytes = read(fd, buf_p, BUFSIZ)) {
        buf = reallocf(buf, (size += BUFSIZ));
        buf_p = buf + size - BUFSIZ;
    }
    errno = 0;
    return buf;
}

char *mx_process_output(char **args) {
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
        execvp(*args, args);
        perror("execvp");
        exit(1);
    }
    return read_output(p[0]);
}
