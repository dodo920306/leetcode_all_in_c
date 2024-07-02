#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int **findDifference(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize, int **returnColumnSizes);

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **findDifference(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize, int **returnColumnSizes)
{
    int **res;
    bool table1[2001] = {false}, table2[2001] = {false};
    if (!(res = (int **)malloc(2 * sizeof(int *))) || !(res[0] = (int *)malloc(nums1Size * sizeof(int))) || !(res[1] = (int *)malloc(nums2Size * sizeof(int))) || !(*returnColumnSizes = (int *)calloc(2, sizeof(int))))
        return NULL;
    *returnSize = 2;
    for (int i = 0; i < nums1Size; i++)
        table1[nums1[i] + 1000] = true;
    for (int i = 0; i < nums2Size; i++)
        table2[nums2[i] + 1000] = true;
    for (int i = 0; i < nums1Size; i++)
        if (!table2[nums1[i] + 1000]) {
            res[0][(**returnColumnSizes)++] = nums1[i];
            table2[nums1[i] + 1000] = true;
        }
    for (int i = 0; i < nums2Size; i++)
        if (!table1[nums2[i] + 1000]) {
            res[1][(*returnColumnSizes)[1]++] = nums2[i];
            table1[nums2[i] + 1000] = true;
        }
    return res;
}

int main()
{
    int nums1[] = {1, 2, 3}, nums2[] = {2, 4, 6}, returnSize, *returnColumnSizes, **res = findDifference(nums1, 3, nums2, 3, &returnSize, &returnColumnSizes);
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        if (i)  printf(", ");
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            if (j)  printf(", ");
            printf("%d", res[i][j]);
        }
        printf("]");
        free(res[i]);
    }
    printf("]\n");
    free(returnColumnSizes);
    free(res);
    return 0;
}
