#include "../inc/ush.h"

static void signal_reload() {
    signal(SIGTSTP, SIG_DFL);
    signal(SIGINT, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
}

int mx_straus_proc(char **args, t_jobs **jobs) {
    pid_t pid;
    int status = 0;

        
    pid = fork();
    if (pid == 0) {
        setpgid(pid, pid);
        signal_reload();
        tcsetpgrp(0, getpid());
        tcsetpgrp(1, getpid());
        execvp(*args, args);
        mx_not_found(args[0], "ush: command");
        exit(127);
    }
    else 
        waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpid());
    tcsetpgrp(1, getpid());
    if (WIFSTOPPED(status)) {
        status = 146;
        mx_add_job(jobs, args, pid);
    }
    else if (WIFSIGNALED(status)) {
        status = 130;
        mx_printstr("\n");
    }
    else if (WIFEXITED(status)) 
        status =  WEXITSTATUS(status);
    errno = 0;
    return status;
}
