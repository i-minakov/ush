#include "../inc/ush.h"

static bool replaced_escaped_smbl(char *s) {
    int ind;

    if ((ind = mx_get_char_index(MX_ECHO_LITERAL_SPEC_CHAR, s[1])) >= 0) {
        s[0] = MX_ECHO_ESC_SPEC_CHAR[ind];
        s[1] = M_SKP;
        return 1;
    }
    return 0;
}

static bool replaced_escaped_hex(char *s) {
    int width = 0;
    char buf[3] = "";

    if (s[1] == 'x') {
        s[0] = M_SKP;
        s[1] = M_SKP;
        if ((isdigit(s[2]) || (s[2] >= 97 && s[2] <= 102))) {
            width++;
            if ((isdigit(s[3]) || (s[3] >= 97 && s[3] <= 102)))
                width++;
        }
        if (width) {
            strncpy(buf, s + 2, width);
            sscanf(buf, "%hhx", s + 2);
            if (width == 2)
                s[3] = M_SKP;
        }
        return 1;
    } 
    return 0;
}

static bool replaced_escaped_octal(char *s) {
    int width = 0;
    char buf[4] = "";

    if (s[1] == '0') {
        s[0] = M_SKP;
        s[1] = M_SKP;
        for (int i = 2; i <= 4 && s[i] >= 48 && s[i] <= 55; i++)
            width++;
        if (width) {
            strncpy(buf, s + 2, width);
            sscanf(buf, "%hho", s + 2);
            if (width >= 2)
                s[3] = M_SKP;
            if (width == 3)
                s[4] = M_SKP;
        }
        return 1;
    } 
    return 0;
}

static void replace_special_chars(char **str) {
    for (char *s = *str; (s = strchr(s, '\\')); s++) {
        if (replaced_escaped_smbl(s) || replaced_escaped_octal(s)
            || replaced_escaped_hex(s)) {
        }
    }
    *str = mx_clear_str(*str);
}

int mx_ush_echo(char **argv) {
    int argc = 0;
    bool flags[NUM_ECHO_FLAGS] = {0, 0, 0};
    int optind = 1;
    char optchar;
    
    while (argv[argc])
        argc++;
    while ((optchar = mx_getopt1(argc, argv, "neE", &optind)) != -1
           && optchar != '?')
        flags[mx_get_char_index("neE", optchar)] = 1;
    if (!flags[ECHO_NOSPEC] || flags[ECHO_SPEC])
        for (char **p = argv + optind; *p; p++)
            replace_special_chars(p);
    for (argv += optind; *argv; argv++) {
        printf("%s", *argv);
        printf(*(argv + 1) ? " " : "");
    }
    if (!flags[ECHO_NONL])
        printf("\n");
    return 0;
}
