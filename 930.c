#include <stdio.h>
#include <stdlib.h>

/**
 * This number was obtained through experiments.
 * If you can't pass the question, it means LeetCode has updated their test inputs, 
 * so please increase the number and report it.
 */
#define MAX_SIZE 29696

int numSubarraysWithSum(int *nums, int numsSize, int goal);

int numSubarraysWithSum(int *nums, int numsSize, int goal)
{
    int res = 0, *map = (int *)calloc(MAX_SIZE, sizeof(int)), mask = (sizeof(int) * CHAR_BIT) - 1;
    /* Each element in map is the number of elements whose prefix sum is the same as the index. */
    if (!map) {
        perror("Error");
        return -1;
    }
    /**
     * The number of previous elements 
     * whose prefix sum is the same as 0 is 1 for nothing.
     */
    *map = 1;
    for (int i = 0, sum = 0, diff; i < numsSize; i++) {
        sum += nums[i];
        diff = sum - goal;
        /**
         * Check if there are previous elements whose prefix sum is the same as the
         * difference between the current sum and goal.
         *
         * If so, 
         * **remove them** respectively to get subarrays ending at nums[i] with a sum goal.
         */
        if (!(diff >> mask) && map[diff])  res += map[diff];
        map[sum]++;
    }
    free(map);
    return res;
}

int main()
{
    int nums[] = {1, 0, 1, 0, 1};
    printf("%d", numSubarraysWithSum(nums, 5, 2));
    return 0;
}
