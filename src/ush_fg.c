#include "../inc/ush.h"

// int no_such(char *name, char *args, char *str) {
//     //name`args: no such str
//     //fg: %3: no such job
//     write(1, name, mx_strlen(name)); //fg:
//     write(1, ": ", 2);
//     write(1, args, mx_strlen(args)); 
//     write(1, ": no such  ", 11);
//     write(1, str, mx_strlen(str));
//     write(1, "\n", 1);
//     return 1;
// }

// int not_found(char *args, char *str) {
//     //fg: job not found: fsh
//     write(1, str, mx_strlen(str));
//     write(1, " not found: ", 12);
//     write(1, args, mx_strlen(args));
//     write(1, "\n", 1);
//     return 1;
// }
//////////////////////////////////////////////

// void del_job(t_jobs **jobs, int flag) {
//     t_jobs *j = *jobs;
//     t_jobs *del = j->next;
    
//     if (flag == 1) { //голова
//         kill(j->pid, SIGCONT);
//         if (j->next == NULL) { //когда один остается
//             if (j->data != NULL) 
//                 mx_del_strarr(&j->data);
//             j->data = NULL;
//             j->num = -1;
//             j->pid = -1;
//             return ;
//         }
//         j->next = NULL;
//         free_jobs(&j);
//         *jobs = del;
//     }
//     if (flag == 2) { //тело
//         kill(del->pid, SIGCONT);
//         j->next = NULL;
//         j->next = del->next;
//         del->next = NULL;
//         free_jobs(&del);
//     }
// }

//////////////////////////////////////////

// static char *cut_str_forjob(char *args) {
//     char *res = NULL;

//     if (args[0] == '\0') //%
//         return res;
//     else if (args[0] != '%') // fg alpha
//         res = mx_strjoin(res, args);
//     else { 
//         for (int i = 1; args[i]; i++)
//             res = mx_strjoin(res, &args[i]);
//     }
//     return res;
// }

/////////////////////////////////////////////

// bool job_num_find(char *args, t_jobs **jobs) {
//     char *tmp = cut_str_forjob(args);
//     int num = mx_atoi(tmp);
//     t_jobs *j = *jobs;
//     bool flag = false;

//     if(j->num == num) { //голова
//         del_job(jobs, 1);
//         flag = true;
//     }
//     else if (j->num > 0 && j->next != NULL) {
//         while(j) { //остальное
//             if(j->next->num == num) {
//                 del_job(&j, 2);
//                 flag = true;
//                 break;
//             }
//             j = j->next;
//             if (j->next == NULL)
//                 break;
//         }
//     }
//     mx_strdel(&tmp); /////null
//     if (flag == false)
//         no_such("fg", args, "job");
//     return flag;
// }
/////////////////////////////////////////////

// bool cur_job(char *tmp , t_jobs **jobs){
//     t_jobs *j = *jobs;
    
//     if (mx_strcmp(tmp, "%") == 0 || //current job последний
//         mx_strcmp(tmp, "+") == 0 || tmp == NULL) { 
//         if (j->data == NULL && j->num == -1) {
//             write (1, "fg: no current job\n", 19);
//             return false;
//         }
//         else if(j->next == NULL) //голова
//             del_job(&j, 1);
//         else {
//             while(j->next->next != NULL)
//                 j = j->next;
//             del_job(&j, 2);
//         }
//     }
//     return true;
// }

// bool prev_job(char *tmp , t_jobs **jobs){
//     t_jobs *j = *jobs;

//     if (mx_strcmp(tmp, "-") == 0) { // previous job предпоследний
//         if (j->next == NULL) {
//             write (1, "fg: no previous job\n", 20);
//             return false;
//         }
//         else if(j->next->next == NULL)
//             del_job(jobs, 1);
//         else {
//             while(j->next->next->next != NULL)
//                 j = j->next;
//             del_job(&j, 2);
//         }
//     }
//     return true;
// }

// int name_search(char *tmp , t_jobs *jobs) {
//     int res = -1;
//     int count = 0;
//     t_jobs *j = jobs;
//     if (j->data != NULL) {
//         while(j) {
//             if (mx_get_substr_index(j->data[0], tmp) == 0)
//                 res = count;
//             j = j->next;
//             count++;
//         }
//     }
//     return res;
// }

// bool name_job(char *tmp , t_jobs **jobs){
//     t_jobs *j = *jobs;
//     int num;

//     if (mx_isalpha(tmp[0])) {
//         num = name_search(tmp , j);
//         if(num == -1) {
//             not_found(tmp, "fg: job"); 
//             return false;
//         }
//         else if (num == 0)
//             del_job(&j, 1);
//         else {
//             while(num - 1){
//                 j = j->next;
//                 num--;
//             }
//             del_job(&j, 2);
//         }
//     }
//     return true;
// }

// bool job_chars_find(char *args, t_jobs **jobs) {
//     char *tmp = cut_str_forjob(args);
//     //t_jobs *j = *jobs;
//     bool flag = true;

//     if (!cur_job(tmp, jobs))
//         flag = false;
//     if (!prev_job(tmp, jobs))
//         flag = false;
//     if (!name_job(tmp, jobs))
//         flag = false;
//     mx_strdel(&tmp);
//     return flag;
// }

/////////////////////////////////////////////

static bool all_digits(char *args){
    for (int i = 1; args[i]; i++) {
        if (!mx_isdigit(args[i]))
            return false;
    }
    return true;
}

static bool pres_persent(char *args, t_jobs **jobs) {

    if (mx_isalpha(args[1]) || args[1] == '-' 
        || args[1] == '+' || args[1] == '%'|| args[1] == '\0') {
        if (!job_chars_find(args, jobs))
                return false;
    }
    else if (all_digits(args)) {
        if (!job_num_find(args, jobs))
            return false;
    }
    else {
        not_found(args, "fg: job"); // любой другой знак
        return false;
    }
    return true; 
}

int ush_fg(char **args, t_jobs **jobs) {

    if (args[1] == NULL) {
        if (job_chars_find("%%", jobs))
                    return 1;
        else 
           return 0; 
    }
    for(int i = 1; args[i]; i++) {
        if (mx_get_char_index(args[i], '%') == 0) {
            if (!pres_persent(args[i], jobs))
                return 1;
        }
        else if (mx_isalpha(args[i][0])) { //букв команда без процента
            if (!job_chars_find(args[i], jobs))
                    return 1;
        }
        else 
            return not_found(args[i], "fg: job");
    }

    // t_jobs *j = *jobs;
    // if (j->data != NULL) {
    //     while(j) {
    //         for (int i = 0; j->data[i]; i++) {
    //             write(1, j->data[i], mx_strlen(j->data[i]));
    //             write(1, " ", 1);
    //         }
    //         mx_printint(j->num);
    //         write(1, " ", 1);
    //         mx_printint(j->pid);
    //         j = j->next;
    //         write(1, "\n", 1);
    //     }
    // }
    // else 
    //     write(1, "+++++/n", 6);

    return 0;
}

