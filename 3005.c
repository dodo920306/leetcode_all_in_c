#include <stdio.h>
#include <limits.h>

int maxFrequencyElements(int* nums, int numsSize);

int maxFrequencyElements(int* nums, int numsSize)
{
    int table[101], max = INT_MIN, res = 0;
    for (int i = 0; i <= 100; table[i++] = 0);

    for (int i = 0; i < numsSize; i++) {
        table[nums[i]]++;
        if (table[nums[i]] > max)   max = table[nums[i]];
    }

    for (int i = 0; i <= 100; res += (table[i++] == max));

    return res * max;
}

int main()
{
    int nums[] = {1, 2, 2, 3, 1, 4};
    printf("%d", maxFrequencyElements(nums, 6));
    return 0;
}
