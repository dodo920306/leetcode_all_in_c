#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

int maxSubarrayLength(int* nums, int numsSize, int k);

int maxSubarrayLength(int* nums, int numsSize, int k)
{
    int min = nums[0], max = nums[0], *counter, res = INT_MIN;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < min)  min = nums[i];
        if (nums[i] > max)  max = nums[i];
    }
    max++;
    counter = (int *)calloc(max - min, sizeof(int));
    if (!counter) {
        perror("Error");
        return errno;
    }
    for (int i = 0, j = 0, length; j < numsSize; j++) {
        counter[nums[j] - min]++;
        while (counter[nums[j] - min] > k)    counter[nums[i++] - min]--;
        length = j - i + 1;
        if (res < length)   res = length;
    }
    free(counter);
    return res;
}

int main()
{
    int nums[] = {1, 2, 3, 1, 2, 3, 1, 2};
    printf("%d\n", maxSubarrayLength(nums, 8, 2));
    return 0;
}
