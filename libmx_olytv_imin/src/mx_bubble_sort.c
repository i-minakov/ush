#include "libmx.h"

int mx_bubble_sort(char **arr, int size)
{
    int f = 1, res = 0;
    char *tmp;
    while (f)
    {
        f = 0;
        for (int i = 0; i < size - 1; i++)
        {
            if (mx_strcmp(arr[i], arr[i + 1]) > 0)
            {
                tmp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = tmp;
                res++;
                f = 1;
            }
        }
    }
    return res;
}
