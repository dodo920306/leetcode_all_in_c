#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);
int majorityElement(int* nums, int numsSize);

int main()
{
    int nums[3] = {3, 2, 3};
    printf("%d\n", majorityElement(nums, 3));
    return 0;
}

int cmp(const void *a,const void *b)
{
    return *(int *)a - *(int *)b;
}

int majorityElement(int* nums, int numsSize)
{
    qsort(nums, numsSize, sizeof(nums[0]), cmp);
    /**
     * After sorted, the element shows up more than (numsSize / 2) times is the majority element,
     * which implies that nums[numsSize / 2] must be the majority element.
     */
    return nums[numsSize / 2];
}
