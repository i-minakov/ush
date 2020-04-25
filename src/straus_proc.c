#include "../inc/ush.h"

static void ctrl_z(int sig) { 
    write(1, "^Z\n", 3);
}

int straus_proc(char **args, t_jobs **jobs) {
    pid_t pid, wait;
    int bins = 0;
    int status;
    int stop = 0;

    signal(SIGTSTP, ctrl_z);
    pid = fork();
    if (pid == 0)
        bins = execvp(*args, args);
    else {
        wait = waitpid(pid, &status, WUNTRACED);
        while (!WIFEXITED(status) && !WIFSIGNALED(status)) {
            if (WIFSTOPPED(status)) {
                add_job(jobs, args, pid);
                break;
            }
            wait = waitpid(pid, &status, WUNTRACED);
            
        }
    }
    errno = 0;
    return bins;
}

