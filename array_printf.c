#include <stdio.h>

void printIntArray(int *, int);
void printStrArray(char **, int);

void printIntArray(int *arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%d, ", arr[i]);
    }
    if (arrSize >= 0)
        printf("%d]\n", arr[arrSize]);
    else
        printf("]\n");
}

void printStrArray(char **arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%s, ", arr[i]);
    }
    if (arrSize >= 0)
        printf("%s]\n", arr[arrSize]);
    else
        printf("]\n");
}
