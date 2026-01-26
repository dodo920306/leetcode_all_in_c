#include <stdio.h>
#include <stdlib.h>

int cmp(const void* a, const void* b);
int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes);

int main() {
    int arr[] = {4, 2, 1, 3};
    int returnSize = 0;
    int* returnColumnSizes = NULL;
    int** res = minimumAbsDifference(arr, 4, &returnSize, &returnColumnSizes);
    printf("[\n");
    for (int i = 0; i < returnSize; i++) {
        printf("    [");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d", res[i][j]);
            if (j + 1 != returnColumnSizes[i]) {
                printf(", ");
            }
        }
        free(res[i]);
        printf("]");
        if (i + 1 != returnSize) {
            printf(",");
        }
        printf("\n");
    }
    free(returnColumnSizes);
    free(res);
    printf("]\n");
    return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    qsort(arr, arrSize, sizeof(int), cmp);
    int minimumDifference = arr[1] - arr[0];
    for (int i = 1; i < arrSize - 1; i++) {
        if (arr[i + 1] - arr[i] < minimumDifference) {
            minimumDifference = arr[i + 1] - arr[i];
        }
    }
    *returnSize = 0;
    for (int i = 0; i < arrSize - 1; i++) {
        if (arr[i + 1] - arr[i] == minimumDifference) {
            (*returnSize)++;
        }
    }
    int** res = (int**)malloc(*returnSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(*returnSize * sizeof(int));
    int currentReturnSize = 0;
    for (int i = 0; i < arrSize - 1; i++) {
        if (arr[i + 1] - arr[i] == minimumDifference) {
            int* returnElement = (int*)malloc(2 * sizeof(int));
            returnElement[0] = arr[i];
            returnElement[1] = arr[i + 1];
            res[currentReturnSize] = returnElement;
            (*returnColumnSizes)[currentReturnSize++] = 2;
        }
    }
    return res;
}

int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

