#include <stdio.h>

#define MAX(a,b) ((a > b) ? a : b)

int maxSubArray(int* nums, int numsSize);

int main()
{
    int nums[9] = {-2,1,-3,4,-1,2,1,-5,4};
    printf("%d\n", maxSubArray(nums, 9));
    return 0;
}

int maxSubArray(int* nums, int numsSize)
{
    int max_sum = nums[0], curr = nums[0];

    for(int i = 1; i < numsSize; i++){
        curr = MAX(nums[i], curr + nums[i]);
        max_sum = MAX(max_sum, curr);
    }
    return max_sum;
}
