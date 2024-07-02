#include <stdio.h>
#include <stdbool.h>

int longestSubarray(int *nums, int numsSize);

int longestSubarray(int *nums, int numsSize)
{
    bool zero = false;
    int i = 0, j = 0, res = 0;
    while (j < numsSize) {
        if (!nums[j]) {
            if (!zero)
                zero = true;
            else
                /* adjust i until only nums[j] == 0 in nums[i:j + 1] */
                while (nums[i++]);
        }
        j++;
        if (res < j - i)
            res = j - i;
    }
    j -= i;
    /* Either with zero or not, an element must be deleted from nums. */
    return res < j ? j - 1 : res - 1;
}

int main()
{
    int nums[] = {0, 1, 1, 1, 0, 1, 1, 0, 1};
    printf("%d\n", longestSubarray(nums, 9));
    return 0;
}
