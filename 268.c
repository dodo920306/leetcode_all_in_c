#include <stdio.h>

int missingNumber(int* nums, int numsSize)
{
    int exist = 0;
    for (int i = 1; i <= numsSize; i++)  exist ^= i;
    for (int i = 0; i < numsSize; i++)  exist ^= nums[i];
    return exist;
}

int main()
{
    int nums[] = {3, 0, 1};
    printf("%d", missingNumber(nums, 3));
    return 0;
}
