#include <stdio.h>

int numSubarrayProductLessThanK(int *nums, int numsSize, int k);

int numSubarrayProductLessThanK(int *nums, int numsSize, int k)
{
    /* No product of a subarray can less than 1 or 0 since all elements here are positive. */
    if (k <= 1) return 0;
    int res = 0;
    for (int i = 0, j = 0, product = 1; j < numsSize; j++) {
        product *= nums[j];
        /* adjust i only when product gets too big */
        while (product >= k)    product /= nums[i++];
        res += j - i + 1; /* all subarrays between them must be valid */
    }
    return res;
}

int main()
{
    int nums[] = {10, 5, 2, 6};
    printf("%d\n", numSubarrayProductLessThanK(nums, 4, 100));
    return 0;
}
