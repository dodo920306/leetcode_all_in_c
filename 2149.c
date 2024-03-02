#include <stdio.h>
#include <stdlib.h>

int* rearrangeArray(int* nums, int numsSize, int* returnSize);

int* rearrangeArray(int* nums, int numsSize, int* returnSize)
{
    int *res = (int *)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;
    if (!res) {
        perror("Error");
        return NULL;
    }

    for (int i = 0, *pos = &res[0], *neg = &res[1], **indir; i < numsSize; i++) {
        indir = (nums[i] >> ((sizeof(int) * CHAR_BIT) - 1)) ? &neg : &pos;
        **indir = nums[i];
        (*indir) += 2;
    }
    return res;
}

int main()
{
    int nums[6] = {3, 1, -2, -5, 2, -4}, returnSize, *res = rearrangeArray(nums, 6, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", res[i]);
    }
    free(res);
    return 0;
}
