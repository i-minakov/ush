#include "../inc/ush.h"

static char *del_button(char *line) {
    char *res = mx_strnew(strlen(line) - 1);

    write(1, "\b \b", 3);
    strncpy(res, line, strlen(line) - 1);
    free(line);
    return res;
}

static char *hist_but(char *line, char *data) {
    for (int i = 0; line != NULL && i < strlen(line); i++)
        write(1, "\b \b", 3);
    mx_strdel(&line);
    write(1, data, mx_strlen(data));
    line = mx_strdup(data);
    return line;
}

static char *stream(int buf, char *line, int *x) {
    char *ch = NULL;

    ch = (char *)(&buf);
    if (buf == 127 && line != NULL && strlen(line) > 0)
        line = del_button(line);
    else if (31 < buf && buf < 127) {
        write(1, ch, 4);
        line = mx_delit_fre(line, ch);
    }
    return line;
}


static char *button(t_hst **hs, char *line, int buf, int *x) {
    t_hst *h = *hs;

    if (buf == 4283163) {
        if (h->next)
            h = h->next;
        line = hist_but(line, h->data);
    }
    if (buf == 4348699) {
        if (h->prev)
            h = h->prev;
        line = hist_but(line, h->data);
    }
    if (buf == 4414235 && *x > 0) {
        printf("%c[1C", 27);
        (*x)--;
    }
    if (buf == 4479771 && line != NULL && strlen(line) > *x) { 
        printf("%c[1D", 27);
        (*x)++;
    }
    *hs = h;
    return line;
}

char *read_stream(t_hst *h) {
    unsigned int buf = 0;
    char *line = NULL;
    int len = 0;
    int x = 0;
    t_hst *head = NULL;
    
    push_f(&h, "\0"); 
    head = h; 
    while ((len = read(0, &buf, 4)) > 0) {
        if (len == 1) {
            if (buf == 10)
                break ;
            line = stream(buf, line, &x);
        }
        if (len > 1) 
            line = button(&h, line, buf, &x);
        buf = 0;
        fflush(stdout);
    }
    free(head->data);
    free(head);
    return line;
}
