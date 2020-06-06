#include "../inc/ush.h"

int builtin(char **args, t_ush *ush) {
    if (!strcmp(args[0], "echo"))
        return mx_ush_echo(args);
    if (!strcmp(args[0], "cd"))
        return mx_ush_cd(args);
    if (!strcmp(args[0], "pwd"))
        return mx_ush_pwd(args);
    if (!strcmp(args[0], "env"))
        return mx_ush_env(args, &ush->jobs);
    if (!strcmp(args[0], "exit"))
        return mx_ush_exit(args, ush);
    if (!strcmp(args[0], "which"))
        return mx_ush_which(args);
    if (!strcmp(args[0], "export"))
        return mx_ush_export(args, &ush->env_set);
    if (!strcmp(args[0], "unset"))
        return mx_ush_unset(args, &ush->env_set);
    if (!strcmp(args[0], "fg"))
        return mx_ush_fg(args, &ush->jobs);
    if (!strcmp(args[0], "jobs"))
        return mx_ush_jobs(args, &ush->jobs);
    return -1;
}

int mx_detect_builds(char **args, t_ush *ush) {
    int bins = 1;

    if (!args || !args[0])
        return 0;
    if ((bins = builtin(args, ush)) != -1) 
        return bins;
    bins = mx_detect_exp(args, ush->hist, &ush->env_set);;
    if (bins != 3) 
        return bins;
    else
        return mx_straus_proc(args, &ush->jobs);
}
