#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int findMaxLength(int *nums, int numsSize);

int findMaxLength(int *nums, int numsSize)
{
    int res = 0, arrSize = (numsSize << 1) + 1, *arr = (int *)malloc(arrSize * sizeof(int));
    if (!arr) {
        perror("Error");
        return errno;
    }

    for (int i = 0; i < arrSize; arr[i++] = -2);
    arr[numsSize] = -1;

    for (int i = 0, count = 0, diff, j; i < numsSize; i++) {
        count += nums[i] ? 1 : -1;
        j = count + numsSize;
        if (arr[j] > -2) {
            diff = i - arr[j];
            if (diff > res) res = diff;
        }
        else    arr[j] = i;
    }
    free(arr);
    return res;
}

int main()
{
    int nums[] = {0, 1};
    printf("%d\n", findMaxLength(nums, 2));
    return 0;
}
