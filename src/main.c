#include "../inc/ush.h"

int detect_builds(char **args, t_ush *ush, t_jobs **jobs) {
    int bins;

    if (!strcmp(args[0], "cd"))
        return ush_cd(args);
    if (!strcmp(args[0], "pwd"))
        return ush_pwd(args);
    if (!strcmp(args[0], "env"))
        return ush_env(args, jobs);
    if (!strcmp(args[0], "exit"))
        return ush_exit(args, ush);
    if (!strcmp(args[0], "which"))
        return ush_which(args);
    if (!strcmp(args[0], "export"))
        return ush_export(args, &ush->env_set);
    if (!strcmp(args[0], "unset"))
        return ush_unset(args, &ush->env_set);
    if (!strcmp(args[0], "fg"))
        return ush_fg(args, jobs);
    bins = straus_proc(args, jobs);
    if (bins == -1) {
        bins = detect_exp(args, ush->hist, &ush->env_set);
        if (bins != 3)
            return bins;
        else {
            not_found(args[0], "ush: command");
            return 1;
        }
    }
    return 0;
}

void ctrl_c(int sig) { 
    pid_t pid = getppid();
    
    write(1, "^C\n", 3);
    kill(pid, SIGINT);
} 

static void start_loop(t_ush *ush, t_jobs *jobs) {
    char *line = NULL;
    struct termios savetty;
    struct termios tty;
    ush->hist = NULL;
    ush->env_set = mx_create_node(NULL);

    signal(SIGINT, ctrl_c);
    while (YARIK_PEREPISIVAYET_LS) {
        tcgetattr(0, &tty);
        savetty = tty; 
        tty.c_lflag &= ~(ICANON|ECHO);
        tty.c_cc[VMIN] = 1;
        tcsetattr(0, TCSAFLUSH, &tty);
        write(1, "u$h> ", mx_strlen("u$h> "));
        line = read_stream(ush->hist);
        write (1, "\n", 1);
        if (line != NULL && mx_strlen(line) > 0) {
            push_f(&ush->hist, line);
            parse(line, ush, &jobs);
        }
        tcsetattr(0, TCSAFLUSH, &savetty);
        if (ush->exit >= 0)
            break ;
    }
    tcsetattr(0, TCSAFLUSH, &savetty);
    free_list2(&ush->env_set);
}

int main(void) {
    int ex = 0;
    t_ush *ush = (t_ush *)malloc(sizeof(t_ush) * 5);
    t_jobs *jobs = mx_create_job(NULL, -1, -1); 

    ush->exit = -1;
    if (isatty(0))
        start_loop(ush, jobs);
    ex = ush->exit;

    free_jobs(&jobs);
    free_list(&ush->hist);
    free(ush);
    exit(ex);
    // system("leaks -q ush");
    return 0;
}
