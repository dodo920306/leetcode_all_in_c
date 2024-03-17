#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int findMaxLength(int *nums, int numsSize);

int findMaxLength(int *nums, int numsSize)
{
    int res = 0, arrSize = (numsSize << 1) + 1, *arr = (int *)malloc(arrSize * sizeof(int));
    if (!arr) {
        perror("Error");
        return errno;
    }

    for (int i = 0; i < arrSize; arr[i++] = -2);
    arr[numsSize] = -1;

    for (int i = 0, count = 0, diff, j; i < numsSize; i++) {
        /**
         * count is the difference between the number of 1s and 0s.
         * It's possible that count < 0 i.e. there are more 0s than 1s.
         * Thus, we created a array as a map indexed by count with size as
         * 2 * numsSize + 1.
         * With count + numsSize as indices,
         * this array can actually accommodate count between
         * [-numsSize, numsSize].
         */
        count += nums[i] ? 1 : -1;
        j = count + numsSize;
        /**
         * If there was the same value of count before,
         * it means that the number of 1s from nums[0] to nums[arr[j]], let us say J1
         * minus the number of 0s from nums[0] to nums[arr[j]], let us say J0, 
         * is the same as
         * the number of 1s from nums[0] to nums[i], let us say I1
         * minus the number of 0s from nums[0] to nums[i], let us say I0
         * i.e. J1 + J0 = I1 + I0.
         * Therefore, I1 - J1 = I0 - J0 i.e.
         * the number of 1s from nums[arr[j + 1]] to nums[i] is the same as
         * the number of 0s from nums[arr[j + 1]] to nums[i] i.e.
         * nums[arr[j] + 1: i + 1] is exactly one of the kind of subarrays we are looking for
         * with length diff = i - arr[j].
         * Therefore, we update the result with max(res, diff)
         */
        if (arr[j] > -2) {
            diff = i - arr[j];
            if (diff > res) res = diff;
        }
        else    arr[j] = i;
    }
    free(arr);
    return res;
}

int main()
{
    int nums[] = {0, 1};
    printf("%d\n", findMaxLength(nums, 2));
    return 0;
}
