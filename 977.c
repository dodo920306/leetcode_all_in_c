#include <stdio.h>
#include <stdlib.h>

#define SIGN ((sizeof(int) * CHAR_BIT) - 1)

int _abs(int n)
{
    int mask = n >> SIGN;
    /**
     * If n >= 0, mask == 0, so ((n + mask) ^ mask) == n.
     * If n < 0, mask == -1, so ((n + mask) ^ mask) == ~(n - 1) == -n (2's complement).
     */
    return (n + mask) ^ mask;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sortedSquares(int *nums, int numsSize, int *returnSize)
{
    int *res = (int *)malloc(numsSize * sizeof(int));
    if (!res) {
        perror ("Error");
        return NULL;
    }
    for (int low = 0, high = numsSize - 1, i = high; low <= high; i--) {
        if (_abs(nums[low]) < _abs(nums[high])) res[i] = nums[high--];
        else res[i] = nums[low++];

        res[i] *= res[i];
    }
    *returnSize = numsSize;
    return res;
}

int main()
{
    int nums[] = {-7, -3, 2, 3, 11}, returnSize = 0, *res = sortedSquares(nums, 5, &returnSize);
    for (int i = 0; i < returnSize; i++)   printf("%d ", res[i]);
    free(res);
    return 0;
}
