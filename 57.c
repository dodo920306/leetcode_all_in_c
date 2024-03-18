#include <stdio.h>
#include <stdlib.h>

void insertAPairAtTheEnd(int **arr, int *arrSize, int *pair, int *arrColSize);
int **insert(int **intervals, int intervalsSize, int *intervalsColSize, 
int *newInterval, int newIntervalSize, int *returnSize, int **returnColumnSizes);

void insertAPairAtTheEnd(int **arr, int *arrSize, int *pair, int *arrColSize)
{
    arr[(*arrSize)] = (int *)malloc(2 * sizeof(int));
    if (!arr[(*arrSize)])   perror("Error");
    else {
        arr[(*arrSize)][0] = pair[0];
        arr[(*arrSize)][1] = pair[1];
        arrColSize[(*arrSize)++] = 2;
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **insert(int **intervals, int intervalsSize, int *intervalsColSize, 
int *newInterval, int newIntervalSize, int *returnSize, int **returnColumnSizes)
{
    int **res = (int **)malloc((intervalsSize + 1) * sizeof(int *)), i = 0;
    *returnColumnSizes = (int *)malloc((intervalsSize + 1) * sizeof(int));
    if (!res || !(*returnColumnSizes)) {
        perror("Error");
        return NULL;
    }

    for ((*returnSize) = 0; i < intervalsSize; i++) {
        if ((intervals[i][0] < newInterval[0] ? newInterval[0] : intervals[i][0]) <= (intervals[i][1] < newInterval[1] ? intervals[i][1] : newInterval[1])) {
            /**
             * MaxStart < MinEnd => Overlap => Merge
             * Update the interval to accommodate the following intervals that should be merged, too.
             * New interval = [minStart, maxEnd];
             */
            newInterval[0] = intervals[i][0] < newInterval[0] ? intervals[i][0] : newInterval[0];
            newInterval[1] = intervals[i][1] < newInterval[1] ? newInterval[1] : intervals[i][1];
        }
        else if (intervals[i][0] < newInterval[0])
            /* No overlap */
            insertAPairAtTheEnd(res, returnSize, intervals[i], *returnColumnSizes);
        else    break;  /* No overlap, but behind the new interval, so we insert the new interval first. */
    }
    /* insert the new interval */
    insertAPairAtTheEnd(res, returnSize, newInterval, *returnColumnSizes);
    while (i < intervalsSize)
        /* add remain intervals that don't overlap with the new interval */
        insertAPairAtTheEnd(res, returnSize, intervals[i++], *returnColumnSizes);

    return res;
}

int main()
{
    int nums1[] = {1, 2}, nums2[] = {3, 5}, nums3[] = {6, 7}, nums4[] = {8, 10}, nums5[] = {12, 16}, 
    *intervals[] = {nums1, nums2, nums3, nums4, nums5}, intervalsColSize[] = {2, 2, 2, 2, 2}, 
    newInterval[] = {4, 8}, returnSize, *returnColumnSizes, 
    **res = insert(intervals, 5, intervalsColSize, newInterval, 2, &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }
    free(returnColumnSizes);
    free(res);
    return 0;
}
