#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int firstMissingPositive(int *nums, int numsSize);

int firstMissingPositive(int *nums, int numsSize)
{
    bool hasOne = false;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1)   hasOne = true;
        /* Make all numbers belong to [1, numsSize]. */
        else if (nums[i] <= 0 || nums[i] > numsSize) nums[i] = 1;
    }
    /* prevent misjudge i.e. there is no 1 in the original array */
    if (!hasOne)    return 1;

    for (int i = 0, index; i < numsSize; i++) {
        /**
         * index belongs to [0, numsSize - 1]
         * use abs() to prevent the number has been marked before
         */
        index = abs(nums[i]) % numsSize;
        /* make nums[index] negative */
        nums[index] = -abs(nums[index]);
    }

    for (int i = 1; i < numsSize; i++)  if (nums[i] > 0)    return i;
    if (nums[0] > 0)    return numsSize;
    return numsSize + 1;
}

int main()
{
    int nums[] = {1, 2, 0};
    printf("%d\n", firstMissingPositive(nums, 3));
    return 0;
}
