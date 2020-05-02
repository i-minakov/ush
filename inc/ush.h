#pragma once
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <locale.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <sys/xattr.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/wait.h>
#include <time.h>
#include <err.h>
#include <signal.h>
#include <stdarg.h>

#include "../libmx/inc/libmx.h"

#define MX_ISEXE(m)      ((m & MX_IFMT) == MX_IFREG && (m & 0111))   
#define MX_ISBLK(m)      (((m) & MX_IFMT) == MX_IFBLK)                  
#define MX_ISCHR(m)      (((m) & MX_IFMT) == MX_IFCHR)                  
#define MX_ISDIR(m)      (((m) & MX_IFMT) == MX_IFDIR)                  
#define MX_ISFIFO(m)     (((m) & MX_IFMT) == MX_IFIFO)                  
#define MX_ISREG(m)      (((m) & MX_IFMT) == MX_IFREG)                  
#define MX_ISLNK(m)      (((m) & MX_IFMT) == MX_IFLNK)                  
#define MX_ISSOCK(m)     (((m) & MX_IFMT) == MX_IFSOCK)                
#define MX_ISWHT(m)      (((m) & MX_IFMT) == MX_IFWHT)                

/* File type */
#define MX_IFMT          0170000    
#define MX_IFIFO         0010000         /* [XSI] named pipe (fifo) */
#define MX_IFCHR         0020000         /* [XSI] character special */
#define MX_IFDIR         0040000         /* [XSI] directory */
#define MX_IFBLK         0060000         /* [XSI] block special */
#define MX_IFREG         0100000         /* [XSI] regular */
#define MX_IFLNK         0120000         /* [XSI] symbolic link */
#define MX_IFSOCK        0140000         /* [XSI] socket */
#define MX_IFWHT         0160000         /* OBSOLETE: whiteout */

/* File mode */
/* Read, write, execute/search by owner */
#define MX_IRWXU         0000700         /* [XSI] RWX mask for owner*/
#define MX_IRUSR         0000400         /* [XSI] R for owner */
#define MX_IWUSR         0000200         /* [XSI] W for owner */
#define MX_IXUSR         0000100         /* [XSI] X for owner */
/* Read, write, execute/search by group */
#define MX_IRWXG         0000070         /* [XSI] RWX mask for group*/
#define MX_IRGRP         0000040         /* [XSI] R for group */
#define MX_IWGRP         0000020         /* [XSI] W for group */
#define MX_IXGRP         0000010      
/* Read, write, execute/search by others */
#define MX_IRWXO         0000007   
#define MX_IROTH         0000004     
#define MX_IWOTH         0000002      
#define MX_IXOTH         0000001       

#define MX_ISUID         0004000     
#define MX_ISGID         0002000     
#define MX_ISVTX         0001000         

#define MX_MAJOR(x)        ((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
#define MX_MINOR(x)        ((int32_t)((x) & 0xffffff))

#define YARIK_PEREPISIVAYET_LS 228

typedef struct s_jobs {
    int num;
    pid_t pid;
    char **data;
    struct s_jobs *next;
}              t_jobs;

typedef struct s_cd {
    int error;
    int flag_s;
    int flag_P;
    int f;
}              t_cd;

typedef struct s_history {
    void *data;
    struct s_history *next;
    struct s_history *prev;
}              t_hst;

typedef struct s_env {
    int flag_i;
    int flag_u;
    char **n;
    char *clear[1];
}              t_env;

typedef struct s_ush {
    int last_return;
    int exit;
    struct s_list *pids;
    struct s_list *env_set;
    struct s_history *hist;
}              t_ush;

// VLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLAD

#include <ctype.h>

#define MX_FUNC_SYMBOLS "\"\'$`(){}\\;"
#define MX_SLASH_SPEC_DBLQ "`$\"\\"
#define MX_SLASH_SPEC "`$\"\\ '(){};~"

#define MX_ERR_PARSE_UNMATCH "ush: parse error: unmatched "
#define MX_ERR_PARSE_CMDSBN "ush: parse error in command substitution\n"
#define MX_ERR_PARSE_BADSBN "ush: bad substitution\n"
#define MX_ERR_PARSE_CLSBRC "ush: closing brace expected\n"
#define MX_ERR_PARSE_CLSPAR "ush: closing parenthesis expected\n"
#define MX_ERR_PARSE_CLSSINQ "ush: closing single quote expected\n"
#define MX_ERR_PARSE_CLSBCKQ "ush: closing backquote expected\n"
#define MX_ERR_PARSE_UNESCDOL "ush: unescaped dollar sign\n"
#define MX_ERR_PARSE_UNESCOPPAR "ush: unescaped (\n"
#define MX_ERR_PARSE_UNESCCLPAR "ush: unescaped )\n"
#define MX_ERR_PARSE_UNESCOPBRC "ush: unescaped {\n"
#define MX_ERR_PARSE_UNESCCLBRC "ush: unescaped }\n"

#define MX_IS_SP_TAB_NL(c) (c == '\n' || c == '\t' || c == ' ')

enum e_quote {
    SIN_Q,
    DBL_Q,
    TDBL_Q,  // temporary opened stack flag
    BCK_Q,
    TBCK_Q,  // temporary opened stack flag
    DOL_CMD,
    TDOL_CMD,  // temporary opened stack flag
    DOL_P,
    DOL_BP,
    SLASH,
    TSLASH,  // temporary opened stack flag
    SEMICOL,
    OUT_CMDS,  // outermost command substitutions list - both ` ` and $()
    OUT_DBQ,  // outermost double quotes list (also not inside of ` ` and $()
    NUM_Q
};

enum e_spec_ch_mark {
    M_SKP = -10,  // skip this char
    M_SKSL,  // slash to be skipped
    M_DEL,  // whitespace word separator delimeter
    M_SEMIC,  // command separator semicolon
    NUM_MC = 4
};


typedef struct s_quotes_params_data {
    int start;
    int end;
}              t_range;

typedef struct s_formatting_list {
    struct s_quotes_params_data *data;
    struct s_formatting_list *next;
}              t_frmt_lst;

// #define MX_ISQUOTE(c) ()

// #include "parse.h"





int mx_check_backquote(char *s, int *i, t_frmt_lst **arr);
int mx_check_single_quote(char *s, int *i, t_frmt_lst **arr);
int mx_check_dollar(char *s, int *i, t_frmt_lst **arr);
void mx_pop_format(t_frmt_lst **del);
void mx_push_format(t_frmt_lst **add, int start, int end, t_frmt_lst **del);
void mx_push_back_format(t_frmt_lst **add, int start, int end,
                         t_frmt_lst **del);
void mx_free_format_lists(t_frmt_lst **arr);
// void mx_mark_chars(char *s, t_frmt_lst **arr);
void mx_break_words_exec(char *s, t_frmt_lst **arr, t_ush *ush, t_jobs **jobs);
void mx_replace_sub_str(char **s, int start, int end, char *replace);
int mx_check_double_quote(char *s, int *i, t_frmt_lst **arr);
int mx_check_open_paren(char *s, int *i, t_frmt_lst **arr);
int mx_check_close_paren(char *s, int *i, t_frmt_lst **arr);
int mx_check_open_brace(char *s, int *i, t_frmt_lst **arr);
int mx_check_close_brace(char *s, int *i, t_frmt_lst **arr);
int mx_get_format_str(char *s, t_frmt_lst **arr);
void mx_param_expansions(char **str, t_frmt_lst **arr, int last_ret_status);
void mx_mark_slash_semicolon_dbl_single_quote(char *s, t_frmt_lst **arr);
char *mx_clear_str(char *str);
char *mx_process_output(char *str, int (*parse_p)(char *, t_ush *, t_jobs **),
                        t_ush *ush, t_jobs **jobs);
t_range *mx_is_inside_of(int i, enum e_quote type, t_frmt_lst **arr);
int mx_cmd_substitution(char **str, t_frmt_lst **arr,
                        t_ush *ush, t_jobs **jobs);
// VLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLADVLAD

void add_job(t_jobs **j, char **args, pid_t pid);
t_jobs *mx_create_job(char **data, int num, pid_t pid);
char **copy_dub_arr(char **args);
void free_jobs(t_jobs **jobs);
void push_f(t_hst **hs, char *data);
int ush_cd(char **args);
int ush_env(char **args, t_jobs **jobs) ;
int ush_exit(char **args, t_ush *ush);
int ush_pwd(char **args);
bool opencheck(char *dirname, t_cd *in);
char *read_stream(t_hst *h);
void free_list(t_hst **list);
void free_list2(t_list **list);
int ush_which(char **args);
int straus_proc(char **args, t_jobs **jobs);
int parse(char *line, t_ush *ush, t_jobs **jobs);
int detect_builds(char **args, t_ush *ush, t_jobs **jobs);

int detect_exp(char **proc, t_hst *start_h, t_list **env_set);
void env_in_list(t_list **env_set, char *src);
int ush_export(char **args, t_list **env_set);
int ush_unset(char **args, t_list **env_set);
int ush_fg(char **args, t_jobs **jobs);
int no_such(char *name, char *args, char *str);
int not_found(char *args, char *str);
void del_job(t_jobs **jobs, int flag);
char *cut_str_forjob(char *args);
bool job_num_find(char *args, t_jobs **jobs);
bool job_chars_find(char *args, t_jobs **jobs);

#define MX_C_FBLACK   "\x1b[30m"
#define MX_C_FRED     "\x1b[31m"
#define MX_C_FGREEN   "\x1b[32m"
#define MX_C_FYELLOW  "\x1b[33m"
#define MX_C_FBLUE    "\x1b[34m"
#define MX_C_FMAGENTA "\x1b[35m"
#define MX_C_FCYAN    "\x1b[36m"
#define MX_C_FWHYTE   "\x1b[37m"

#define MX_C_BBLACK   "\x1b[40m"
#define MX_C_BRED     "\x1b[41m"
#define MX_C_BGREEN   "\x1b[42m"
#define MX_C_BYELLOW  "\x1b[43m"
#define MX_C_BBLUE    "\x1b[44m"
#define MX_C_BMAGENTA "\x1b[45m"
#define MX_C_BCYAN    "\x1b[46m"
#define MX_C_BWHYTE   "\x1b[47m"

#define MX_C_BOLD     "\x1b[1m"
#define MX_C_RESET    "\x1b[0m"

