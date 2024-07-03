#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);
int minDifference(int *nums, int numsSize);

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int minDifference(int *nums, int numsSize)
{
    int possibleDifferences[4];

    if (numsSize < 5)
        /* All elements can be changed to the same value. */
        return 0;
    qsort(nums, numsSize, sizeof(int), cmp);
    /**
     * For arrays with more than 4 elements,
     * there are 4 possible scenarios we can perform to get smaller difference.
     *
     * 1. Change the three largest elements into the fourth largest element.
     * 2. Change the two largest elements into the third largest element and
     *    the one smallest element into the second smallest element.
     * 3. Change the one largest element into the second largest element and
     *    the two smallest elements into the third smallest element.
     * 4. Change the three smallest elements into the fourth smallest element.
     *
     * Other scenarios without changing either largest or smallest elements
     * won't reduce the overall difference.
     */
    possibleDifferences[0] = nums[numsSize - 4] - nums[0];
    possibleDifferences[1] = nums[numsSize - 3] - nums[1];
    possibleDifferences[2] = nums[numsSize - 2] - nums[2];
    possibleDifferences[3] = nums[numsSize - 1] - nums[3];
    qsort(possibleDifferences, 4, sizeof(int), cmp);
    return *possibleDifferences;
}

int main()g
{
    int nums[] = {1, 5, 0, 10, 14};
    printf("%d\n", minDifference(nums, 5));
    return 0;
}
