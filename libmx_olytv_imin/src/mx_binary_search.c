#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count)
{
    if (arr == NULL || *arr == 0) return -1;
    int right = size - 1, left = 0;
    while (left <= right)
    {
        *count += 1;
        int mid = (left + right) / 2;
        if (mx_strcmp(arr[mid], s) < 0) left = mid + 1;
        else if (mx_strcmp(arr[mid], s) > 0) right = mid - 1;
        else return mid;
    }
    *count = 0;
    return -1;
}
