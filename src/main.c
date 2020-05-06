#include "../inc/ush.h"

static void handel(int sig) { 
    pid_t pid = getpid();
    
    if (pid == 0 && sig == 2) {
        write(1, "^C\n", 3);
        kill(pid, SIGINT);
    }
    if (pid == 0 && sig == 20)
        write(1, "^Z\n", 3);
} 

static void start_loop(t_ush *ush) {
    char *line = NULL;
    struct termios savetty;
    struct termios tty;
    ush->hist = NULL;
    ush->env_set = mx_create_node(NULL);

    signal(SIGINT, handel);
    signal(SIGTSTP, handel);
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
            mx_parse(line, ush);
            system("leaks -q ush");
        }
        tcsetattr(0, TCSAFLUSH, &savetty);
        if (ush->exit >= 0)
            break ;
    }
    free_list2(&ush->env_set);
}

static void pipe_call(t_ush *ush) {
    int buf = 0;
    char *line = NULL;
    char *ch = NULL;

    while (read(STDIN_FILENO, &buf, 3) > 0) {
        ch = (char *)(&buf);
        line = mx_delit_fre(line, ch);
        buf = 0;
    }
    mx_parse(line, ush);
    system("leaks -q ush");
}

static void set_shell_lvl_up(void) {
    char *s;

    if (getppid() == 1)
        return;
    s = mx_itoa((atoi(getenv("SHLVL"))) + 1);
    setenv("SHLVL", s, 1);
    free(s);
}

int main(void) {
    int ex = 0;
    t_ush *ush = (t_ush *)calloc(6, sizeof(t_ush));
    ush->jobs = mx_create_job(NULL, -1, -1, NULL);
    set_shell_lvl_up();

    ush->exit = -1;
    if (isatty(0)) {
        start_loop(ush);
        ex = ush->exit;
        free_list(&ush->hist);
        exit(ex);
    }
    else
        pipe_call(ush);
    free_jobs(&ush->jobs);
    free(ush);
    return 0;
}
