#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int firstMissingPositive(int *nums, int numsSize);

int firstMissingPositive(int *nums, int numsSize)
{
    bool hasOne = false;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1)   hasOne = true;
        else if (nums[i] <= 0 || nums[i] > numsSize) nums[i] = 1;
    }
    if (!hasOne)    return 1;

    for (int i = 0, index; i < numsSize; i++) {
        index = abs(nums[i]) % numsSize;
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
