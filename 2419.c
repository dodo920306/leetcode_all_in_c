#include <stdio.h>

#define UPDATE_MAXIMUM(max, current) \
    do { \
        int _current = (current); \
        if ((max) < _current) { \
            (max) = _current; \
        } \
    } while (0)

int findMaxOfNums(int *nums, int numsSize);
int longestSubarray(int *nums, int numsSize);

int findMaxOfNums(int *nums, int numsSize)
{
    int res = *nums;
    for (int i = 1; i < numsSize; i++)
        UPDATE_MAXIMUM(res, nums[i]);
    return res;
}

int longestSubarray(int *nums, int numsSize)
{
    int res = 1, maximum = findMaxOfNums(nums, numsSize);
    for (int i = 0, current = 0; i < numsSize; i++)
        if (nums[i] == maximum)
            UPDATE_MAXIMUM(res, ++current);
        else
            current = 0;
    return res;
}

int main()
{
    int nums[] = {1, 2, 3, 3, 2, 2};
    printf("%d\n", longestSubarray(nums, 6));
    return 0;
}
