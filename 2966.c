#include <stdio.h>
#include <stdlib.h>

void countingsort(int *nums, int numsSize);
int** divideArray(int* nums, int numsSize, int k, int* returnSize, int** returnColumnSizes);

void countingsort(int *nums, int numsSize)
{
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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** divideArray(int* nums, int numsSize, int k, int* returnSize, int** returnColumnSizes)
{
    int **res;

    /**
     * Use counting sort to sort the array to provide O(n) time complexity.
     * This is valid since the values of elements are between 1 and 100000 in this question.
     */
    countingsort(nums, numsSize);

    for (int i = 0; i < numsSize; i += 3)
        if (nums[i + 2] - nums[i] > k) {
            *returnSize = 0;
            return NULL;
        }
    *returnSize = numsSize / 3;
    *returnColumnSizes = (int *)malloc(*returnSize * sizeof(int));
    res = (int **)malloc(*returnSize * sizeof(int *));
    if (!*returnColumnSizes || !res) {
        perror("Error");
        return NULL;
    }
    for (int i = 0, j; i < *returnSize; i++) {
        res[i] = (int *)malloc(3 * sizeof(int));
        if (!res[i]) {
            perror("Error");
            return NULL;
        }
        (*returnColumnSizes)[i] = 3;
        j = 3 * i;
        res[i][0] = nums[j];
        res[i][1] = nums[j + 1];
        res[i][2] = nums[j + 2];
    }
    return res;
}

int main()
{
    int nums[] = {1,3,4,8,7,9,3,5,1}, returnSize, *returnColumnSizes, **res = divideArray(nums, 9, 2, &returnSize, &returnColumnSizes);
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++)
            printf("%d,", res[i][j]);
        free(res[i]);
        printf("]");
    }
    printf("]");
    free(res);
    free(returnColumnSizes);
    return 0;
}
