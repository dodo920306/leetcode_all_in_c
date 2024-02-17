#include <stdio.h>
#include <stdlib.h>

/* This can only be used when the range of the values of the elements is small. */
void countingsort(int *nums, int numsSize)
{
    if (!numsSize)  return;
    int min = INT_MAX, max = INT_MIN;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max)  max = nums[i];
        if (min > nums[i])  min = nums[i];
    }
    max++;
    int *freq = (int *)calloc(max - min, sizeof(int));
    if (!freq) {
        perror("Error");
        return;
    }
    for (int i = 0; i < numsSize; i++) freq[nums[i] - min]++;
    for (int i = 0, j = 0; i < numsSize; j++)
        while (freq[j]--)   nums[i++] = j + min;
    free(freq);
}

int main() {
    int nums[] = {1,3,4,8,7,9,3,5,1};
    countingsort(nums, 9);
    printf("[");
    for (int i = 0; i < 9; i++) {
        printf("%d,", nums[i]);
    }
    printf("]");
    return 0;
}
