#include <stdio.h>

int maxI(int *nums, int numsSize);
long long largestPerimeter(int *nums, int numsSize);

int maxI(int *nums, int numsSize)
{
    int max = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[max])  max = i;
    }
    return max;
}

long long largestPerimeter(int *nums, int numsSize)
{
    long long perimeter = 0;
    for (int i = 0; i < numsSize; i++)
        perimeter += nums[i];

    for (int i = numsSize, max; i > 2; i--) {
        /**
         * We don't use qsort here since the average time will thus be O(nlogn).
         * Although the time spent on get the current maximum will be O(1),
         * what we only need for every round is 
         * to get the maximum and check if it's valid to decide whether to delete it.
         * The above things can be done in O(n), so we don't waste O(nlogn).
         * Instead, we try to get the maximum every round.
         * i in loops here is simply a counter.
         */
        max = maxI(nums, numsSize);
        perimeter -= nums[max];
        /* valid */
        if (perimeter > nums[max])    return perimeter + nums[max];
        /* invalid => delete. The edges won't be 0 originally, so it's safe to do so. */
        nums[max] = 0;
    }
    return -1;
}

int main()
{
    return 0;
}
