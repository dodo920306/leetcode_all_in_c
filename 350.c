#include <stdio.h>
#include <stdlib.h>

int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *intersect(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize)
{
    if (nums2Size < nums1Size)
        return intersect(nums2, nums2Size, nums1, nums1Size, returnSize);

    int *res, *table1, *table2;
    if (!(res = (int *)malloc(nums1Size * sizeof(int))) || !(table1 = (int *)calloc(1001, sizeof(int))) || !(table2 = (int *)calloc(1001, sizeof(int))))
        return NULL;
    for (int i = 0; i < nums1Size; i++) {
        table1[nums1[i]]++;
        table2[nums2[i]]++;
    }
    for (int i = nums1Size; i < nums2Size; i++)
        table2[nums2[i]]++;
    *returnSize = 0;
    for (int i = 0, j = 0; i <= 1000; i++) {
        j = table1[i] < table2[i] ? table1[i] : table2[i];
        while (j--)
            res[(*returnSize)++] = i;
    }
    free(table1);
    free(table2);
    return res;
}

int main()
{
    int nums1[] = {1, 2, 2, 1}, nums2[] = {2, 2}, returnSize, *res = intersect(nums1, 4, nums2, 2, &returnSize);
    returnSize--;
    printf("[");
    for (int i = 0; i < returnSize; i++)
        printf("%d, ", res[i]);
    printf("%d]\n", res[returnSize]);
    free(res);
    return 0;
}
