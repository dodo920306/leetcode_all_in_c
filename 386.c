#include <stdio.h>
#include <stdlib.h>

int *lexicalOrder(int , int *);
void printIntArray(int *, int);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *lexicalOrder(int n, int *returnSize)
{
    int *res = (int *)malloc(n * sizeof(int));
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    *returnSize = 0;
    for (int i = 1; (*returnSize) < n;)
        if (i <= n) {
            res[(*returnSize)++] = i;
            i *= 10;
        }
        else {
            do {
                i /= 10;
            } while (i % 10 == 9);
            i++;
        }

    return res;
}

void printIntArray(int *arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%d, ", arr[i]);
    }
    if (arrSize >= 0)
        printf("%d]\n", arr[arrSize]);
    else    printf("]\n");
}

int main()
{
    int returnSize, *res = lexicalOrder(13, &returnSize);
    printIntArray(res, returnSize);
    free(res);
    return 0;
}
