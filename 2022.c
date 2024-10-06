#include <stdio.h>
#include <stdlib.h>

int **construct2DArray(int *, int, int, int, int *, int **);
void printIntArray(int *, int);

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **construct2DArray(int *original, int originalSize, int m, int n, int *returnSize, int **returnColumnSizes)
{
    int **res = NULL;
    *returnSize = 0;
    if (originalSize != m * n)
        return NULL;

    *returnColumnSizes = (int *)calloc(m, sizeof(int));
    res = (int **)malloc(m * sizeof(int *));
    if (!(*returnColumnSizes && res)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    for (int i = 0; i < m; i++) {
        res[i] = (int *)malloc(n * sizeof(int));
        if (!(res[i])) {
            fprintf(stderr, "Error: Memory Allocation Failed.");
            return res;
        }

        (*returnColumnSizes)[i] = n;
        for (int j = 0; j < n; j++)
            res[i][j] = original[i * n + j];
    }

    *returnSize = m;
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
    else
        printf("]\n");
}

int main()
{
    int original[] = {1, 2, 3, 4}, returnSize = 0, *returnColumnSizes = NULL, **res = construct2DArray(original, 4, 2, 2, &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; i++) {
        printIntArray(res[i], returnColumnSizes[i]);
        free(res[i]);
    }

    free(returnColumnSizes);
    free(res);
    return 0;
}
