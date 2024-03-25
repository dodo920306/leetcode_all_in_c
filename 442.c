#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int *findDuplicates(int *nums, int numsSize, int *returnSize);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *findDuplicates(int *nums, int numsSize, int *returnSize)
{
    bool *t = (bool *)calloc(numsSize + 1, sizeof(bool));
    int *res = (int *)malloc(numsSize * sizeof(int));
    if (!t || !res) {
        perror("Error");
        return NULL;
    }
    *returnSize = 0;
    for (int i = 0; i < numsSize; i++) {
        if (t[nums[i]]) res[(*returnSize)++] = nums[i];
        else    t[nums[i]] = true;
    }
    free(t);
    return res;
}

int main()
{
    int nums[] = {4, 3, 2, 7, 8, 2, 3, 1}, returnSize, *res = findDuplicates(nums, 8, &returnSize);
    for (int i = 0; i < returnSize; i++)    printf("%d ", res[i]);
    printf("\n");
    free(res);
    return 0;
}
