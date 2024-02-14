#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);
int **merge(int **intervals, int intervalsSize, int *intervalsColSize, int *returnSize, int **returnColumnSizes);

int cmp(const void *a, const void *b)
{
    return **(int **)a - **(int **)b;
}

int **merge(int **intervals, int intervalsSize, int *intervalsColSize, int *returnSize, int **returnColumnSizes)
{
    int **res = (int **)malloc(intervalsSize * sizeof(int *)), top = 0;
    if (!res) {
        perror("Error");
        return NULL;
    }
    *returnColumnSizes = intervalsColSize;

    /* Sort first, so the next interval must start later. */
    qsort(intervals, intervalsSize, sizeof(int *), cmp);

    *res = *intervals;
    for (int i = 1; i < intervalsSize; i++) {
        if (res[top][1] > intervals[i][0]) {
            if (intervals[i][1] > res[top][1])
                /* The next interval starts later and ends later => merge. */
                res[top][1] = intervals[i][1];
            /* The next interval starts later and ends earlier => omit. */
        }
        else if (res[top][1] == intervals[i][0])
            /* The next interval must end later => merge. */
            res[top][1] = intervals[i][1];
        else
            /* No overlap => push. */
            res[++top] = intervals[i];
    }

    *returnSize = ++top;
    return res;
}

int main()
{
    int intervalsSize = 4, intervalsColSize[4] = {2, 2, 2, 2}, **intervals = (int **)malloc(4 * sizeof(int *)), returnSize, *returnColumnSizes, **res;
    if (!intervals) {
        perror("Error");
        return 1;
    }
    for (int i = 0; i < 4; i++) {
        intervals[i] = (int *)malloc(sizeof(int[2]));
        if (!intervals[i]) {
            perror("Error");
            return i + 2;
        }
    }

    intervals[0][0] = 1;
    intervals[0][1] = 3;
    intervals[1][0] = 2;
    intervals[1][1] = 6;
    intervals[2][0] = 8;
    intervals[2][1] = 10;
    intervals[3][0] = 15;
    intervals[3][1] = 18;

    res = merge(intervals, intervalsSize, intervalsColSize, &returnSize, &returnColumnSizes);

    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < 2; j++)
            printf("%d ", res[i][j]);
        printf("\n");
    }

    for (int i = 0; i < 4; i++) free(intervals[i]);
    free(intervals);
    free(res);
    return 0;
}
