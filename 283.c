#include <stdio.h>

void moveZeroes(int *nums, int numsSize)
{
    int nonzero = 0;
    while (nonzero < numsSize && nums[nonzero])  nonzero++;
    for (int i = nonzero + 1; i < numsSize; i++)
        if (nums[i])    nums[nonzero++] = nums[i];
    while (nonzero < numsSize)  nums[nonzero++] = 0;
}

int main()
{
    int nums[] = {0, 1, 0, 3, 12};
    moveZeroes(nums, 5);
    printf("[");
    for (int i = 0; i < 4; i++) printf("%d, ", nums[i]);
    printf("%d]\n", nums[4]);
    return 0;
}
