#include <stdio.h>

int longestOnes(int *nums, int numsSize, int k);

int longestOnes(int *nums, int numsSize, int k)
{
    int i = 0, j = 0, zero = 0, res = 0;
    while (j < numsSize)
        if (zero <= k) {
            if (res < j - i)
                res = j - i;
            zero += !nums[j];
            j++;
        }
        else {
            zero -= !nums[i];
            i++;
        }

    if (zero <= k && res < j - i)
        res = j - i;
    return res;
}

int main()
{
    int nums[] = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
    printf("%d\n", longestOnes(nums, 19, 3));
    return 0;
}
