#include <stdio.h>
#include <stdlib.h>

int *xorQueries(int *, int, int **, int, int *, int *);

void printIntArray(int *, int);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *xorQueries(int *arr, int arrSize, int **queries, int queriesSize, int *queriesColSize, int *returnSize)
{
    int *res = (int *)malloc(queriesSize * sizeof(int));
    *returnSize = 0;
    if (!res)   return NULL;

    for (int i = 1; i < arrSize; i++)
        arr[i] = arr[i - 1] ^ arr[i];

    for (int i = 0; i < queriesSize; i++)
        res[i] = queries[i][0] ?
                    arr[queries[i][0] - 1] ^ arr[queries[i][1]] :
                    arr[queries[i][1]];
    *returnSize = queriesSize;

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
    int arr[] = {1, 3, 4, 8},
        query1[] = {0, 1},
        query2[] = {1, 2},
        query3[] = {0, 3},
        query4[] = {3, 3},
        *queries[4] = {query1, query2, query3, query4},
        queriesColSize[] = {2, 2, 2, 2},
        returnSize = 0,
        *res = xorQueries(arr, 4, queries, 4, queriesColSize, &returnSize);
    printIntArray(res, returnSize);
    free(res);
    return 0;
}
