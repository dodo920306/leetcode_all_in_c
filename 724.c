#include <stdio.h>

int pivotIndex(int *nums, int numsSize);

int pivotIndex(int *nums, int numsSize)
{
    int leftSum = 0, rightSum = 0;
    for (int i = 1; i < numsSize; i++)
        rightSum += nums[i];
    if (!rightSum)
        /* pivot is 0. */
        return 0;
    for (int i = 1; i < numsSize; i++) {
        /* add the last element */
        leftSum += nums[i - 1];
        /* minus the pivot */
        rightSum -= nums[i];
        if (leftSum == rightSum)
            return i;
    }
    return -1;
}

int main()
{
    int nums[] = {1, 7, 3, 6, 5, 6};
    printf("%d\n", pivotIndex(nums, 6));
    return 0;
}
