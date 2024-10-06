#include <stdio.h>
#include <stdlib.h>

int *missingRolls(int *, int, int, int, int *);
void printIntArray(int *, int);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *missingRolls(int *rolls, int rollsSize, int mean, int n, int *returnSize)
{
    int sum = (rollsSize + n) * mean, *res = (int *)malloc(n * sizeof(int));
    *returnSize = 0;
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    for (int i = 0; i < rollsSize; i++) sum -= rolls[i];

    if (n <= sum && sum <= 6 * n) {
        *returnSize = n;
        for (int i = 0, avg = sum / n; i < n; i++)  res[i] = avg;
        for (int i = 0, remainder = sum % n; i < remainder; i++)  res[i]++;
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
    else
        printf("]\n");
}

int main()
{
    int returnSize = 0, \
        rolls[] = {3, 2, 4, 3}, \
        *res = missingRolls(rolls, 4, 4, 2, &returnSize);
    printIntArray(res, returnSize);
    return 0;
}
