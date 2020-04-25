#pragma once
// #include <ush.h>
#include <ctype.h>

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

#define MX_FUNC_SYMBOLS "\"\'$`(){}\\;"
#define MX_SLASH_SPEC_DBLQ "`$\"\\"
#define MX_SLASH_SPEC "`$\"\\ '(){};~"
#define MX_ERR_PARSE_CMDSBN "ush: parse error in command substitution\n"
#define MX_ERR_PARSE_BADSBN "ush: bad substitution\n"
#define MX_ERR_PARSE_CLSBRC "ush: closing brace expected\n"
#define MX_ERR_PARSE_CLSPAR "ush: closing parenthesis expected\n"
#define MX_ERR_PARSE_CLSSINQ "ush: closing single quote expected\n"
#define MX_ERR_PARSE_UNESCDOL "ush: unescaped dollar sign\n"
#define MX_ERR_PARSE_UNESCOPPAR "ush: unescaped (\n"
#define MX_ERR_PARSE_UNESCCLPAR "ush: unescaped )\n"
#define MX_ERR_PARSE_UNESCOPBRC "ush: unescaped {\n"
#define MX_ERR_PARSE_UNESCCLBRC "ush: unescaped }\n"


enum e_quote {
    SIN_Q,
    DBL_Q,
    TDBL_Q,  //temporary opened stack flag
    BCK_Q,
    TBCK_Q,  //temporary opened stack flag
    DOL_CMD,
    TDOL_CMD,  //temporary opened stack flag
    DOL_BP,
    DOL_P,
    SLASH,
    TSLASH,  //temporary opened stack flag
    SEMICOL,
    NUM_Q
};

typedef struct s_quotes_params_data {
    enum e_quote type;
    int start;
    int end;
}              t_qts_params;

typedef struct s_formatting_list {
    struct s_quotes_params_data *data;
    struct s_formatting_list *next;
}              t_frmt_lst;

// #define MX_ISQUOTE(c) ()
