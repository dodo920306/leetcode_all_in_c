#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);
int maxOperations(int *nums, int numsSize, int k);

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int maxOperations(int *nums, int numsSize, int k)
{
    int i = 0, j = numsSize - 1, res = 0;
    qsort(nums, numsSize, sizeof(int), cmp);
    while (i < j)
        if (nums[i] + nums[j] > k)  j--;
        else if (nums[i] + nums[j] < k) i++;
        else {
            res++;
            i++;
            j--;
        }
    return res;
}

int main()
{
    int nums[] = {3, 1, 3, 4, 3};
    printf("%d\n", maxOperations(nums, 5, 6));
    return 0;
}
