#include <stdio.h>

int* minBitwiseArray(int* nums, int numsSize, int* returnSize);
int minBitwiseNum(int num);

int main()
{
    int nums[] = {2, 3, 5, 7};
    int returnSize = 0;
    int* res = minBitwiseArray(nums, 4, &returnSize);
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", res[i]);
        if (i + 1 != returnSize) {
            printf(", ");
        }
    }
    printf("]\n");
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* minBitwiseArray(int* nums, int numsSize, int* returnSize)
{
    for (int i = 0; i < numsSize; i++) {
        nums[i] = minBitwiseNum(nums[i]);
    }
    *returnSize = numsSize;
    return nums;
}

int minBitwiseNum(int num)
{
    if (!(num & 1)) {
        return -1;
    }
    if (!(num & (num - 1))) {
        return num >> 1;
    }
    int bit = 1;
    for (; num & (bit << 1); bit <<= 1);
    return num - bit;
}
