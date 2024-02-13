#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);
int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize);

int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize)
{
    qsort(nums, numsSize, sizeof(int), cmp);
    int *dp = (int *)malloc(numsSize * sizeof(int)), *size = (int *)malloc(numsSize * sizeof(int)), *res, index = 0;
    if (!dp) {
        perror("Error");
        return NULL;
    }
    if (!size) {
        perror("Error");
        return NULL;
    }
    *returnSize = INT_MIN;
    for (int i = 0; i < numsSize; i++)
    {
        /* At first, a Largest Divisible Subset (LDS) ending at i has at least one element 'i' itself. */
        dp[i] = i;
        size[i] = 1;
        for (int j = 0; j < i; j++)
        {
            /**
             * For every i, consider if there is any j whose LDS can be included in the LDS of i
             * i.e. j|i and size[j] + 1 could be larger than the original size[i].
             */
            if (!(nums[i] % nums[j]) && size[i] <= size[j]) {
                size[i] = size[j] + 1;
                dp[i] = j;
            }
        }
        /* Then, include the next i into the considering */
    }
    for (int i = 0; i < numsSize; i++)
    {
        if (*returnSize < size[i]) {
            *returnSize = size[i];
            index = i;
        }
    }
    res = (int *)malloc(*returnSize * sizeof(int));
    if (!res) {
        perror("Error");
        return NULL;
    }
    for (int i = *returnSize - 1; i >= 0; i--)
    {
        res[i] = nums[index];
        index = dp[index];
    }
    return res;
}

int main()
{
    int nums[3] = {1, 2, 3}, numsSize = 3, returnSize = 0, *res = largestDivisibleSubset(nums, numsSize, &returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("%d ", res[i]);
    }
    free(res);
    return 0;
}
