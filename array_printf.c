#include <stdio.h>

void printIntArray(int *arr, int arrSize);

void printIntArray(int *arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[arrSize]);
}
