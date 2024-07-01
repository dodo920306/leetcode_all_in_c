#include <stdio.h>

double findMaxAverage(int *nums, int numsSize, int k);

double findMaxAverage(int *nums, int numsSize, int k)
{
    double res, sum = 0;
    for (int i = 0; i < k; i++) sum += nums[i];
    res = sum;
    for (int i = 0; i + k < numsSize; i++) {
        sum += nums[i + k] - nums[i];
        if (res < sum)  res = sum;
    }
    return res / k;
}

int main()
{
    int nums[] = {1, 12, -5, -6, 50, 3};
    printf("%lf\n", findMaxAverage(nums, 6, 4));
    return 0;
}
