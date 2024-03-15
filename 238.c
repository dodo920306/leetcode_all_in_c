#include <stdio.h>

int *productExceptSelf(int *nums, int numsSize, int *returnSize)
{
    int product = 1, zeros = 0;
    for (int i = 0; i < numsSize && zeros < 2; i++)
        if (!nums[i])   zeros++;
        /* product is the product of all non-zero elements. */
        else    product *= nums[i];

    if (!zeros)
        for (int i = 0; i < numsSize; nums[i++] = product / nums[i]);
    else if (zeros == 1)
        /* Every one is 0 except the element that was originally 0. */
        for (int i = 0; i < numsSize; nums[i++] = nums[i] ? 0 : product);
    else
        /* all 0s */
        for (int i = 0; i < numsSize; nums[i++] = 0);

    *returnSize = numsSize;
    return nums;
}

int main()
{
    int nums[] = {1, 2, 3, 4}, returnSize, *res = productExceptSelf(nums, 4, &returnSize);
    for (int i = 0; i < returnSize; printf("%d ", res[i++]));
    return 0;
}
