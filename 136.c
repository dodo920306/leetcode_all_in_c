#include <stdio.h>

int singleNumber(int* nums, int numsSize);

int main()
{
    int nums[5] = {4,1,2,1,2};
    printf("%d\n", singleNumber(nums, 5));
    return 0;
}

int singleNumber(int* nums, int numsSize)
{
    int num = nums[0];
    for (int i = 1; i < numsSize; i++){
        num ^= nums[i];
    }
    return num;
}
