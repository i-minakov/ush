#include "../inc/ush.h"

static void reload(pid_t pid, char **args, t_jobs **jobs) {
    int status;

    tcsetpgrp(0, pid);
    tcsetpgrp(1, pid);
    kill(pid, SIGCONT);
    waitpid(pid, &status, WUNTRACED);
    tcsetpgrp(0, getpid());
    tcsetpgrp(1, getpid());
    if (WIFSTOPPED(status)) {
        // mx_del_strarr(&args);
        mx_add_job(jobs, args, pid);
    }
    if (args != NULL)
        mx_del_strarr(&args);
    errno = 0;
}

static void del_body(t_jobs **jobs) {
    t_jobs *j = *jobs;
    t_jobs *del = j->next;
    char **data = mx_copy_dub_arr(del->data);
    
    int pid = del->pid;
    j->next = NULL;
    j->next = del->next;
    del->next = NULL;
    mx_free_jobs(&del);
    reload(pid, data, jobs);
}

void mx_del_job(t_jobs **jobs, int flag) {
    t_jobs *j = *jobs;
    t_jobs *del = j->next;
    char **data = NULL;
    int pid = j->pid;
    
    if (flag == 1) {
        data = mx_copy_dub_arr(j->data);
        if (j->next == NULL) { //когда один остается
            if (j->data != NULL) 
                mx_del_strarr(&j->data);
            mx_strdel(&j->pwd);
            j->data = NULL;
            j->num = -1;
            j->pid = -1;
            reload(pid, data, &j);
        }
        else {
            j->next = NULL;
            mx_free_jobs(&j);
            *jobs = del;
            reload(pid, data, jobs);
        }
    }
    if (flag == 2) { //тело
        del_body(jobs);
    }
}
