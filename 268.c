#include <stdio.h>

int missingNumber(int *nums, int numsSize)
{
    int res = 0;
    for (int i = 1; i <= numsSize; i++)  res ^= i;
    for (int i = 0; i < numsSize; i++)  res ^= nums[i];
    return res;
}

int main()
{
    int nums[] = {3, 0, 1};
    printf("%d", missingNumber(nums, 3));
    return 0;
}
