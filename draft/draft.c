#include "../inc/parse.h"


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
