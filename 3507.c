#include <stdio.h>
#include <stdbool.h>

int minimumPairRemoval(int* nums, int numsSize)
{
    bool isNotDecreasing = true;
    int res = 0;
    while (isNotDecreasing && numsSize > 1) {
        int minimumSum = nums[0] + nums[1];
        int minimumSumIndex = 0;
        isNotDecreasing = nums[0] > nums[1];
        for (int i = 1; i < numsSize - 1; i++) {
            if (nums[i] + nums[i + 1] < minimumSum) {
                minimumSum = nums[i] + nums[i + 1];
                minimumSumIndex = i;
            }
            if (nums[i] > nums[i + 1]) {
                isNotDecreasing = true;
            }
        }
        if (isNotDecreasing) {
            nums[minimumSumIndex] += nums[minimumSumIndex + 1];
            for (int i = minimumSumIndex + 1; i < numsSize - 1; i++) {
                nums[i] = nums[i + 1];
            }
            numsSize--;
            res++;
        }
    }
    return res;
}

int main()
{
    int nums[] = {5, 2, 3, 1};
    printf("%d\n", minimumPairRemoval(nums, 4));
    return 0;
}
