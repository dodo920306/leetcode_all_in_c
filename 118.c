#include <stdio.h>
#include <stdlib.h>

int** generate(int numRows, int* returnSize, int** returnColumnSizes);

int main()
{
    int numRows = 5, returnSize, *returnColumnSizes;
    int **ans = generate(numRows, &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < returnColumnSizes[i]; j++) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** generate(int numRows, int* returnSize, int** returnColumnSizes)
{
    int **ans = (int **)malloc(numRows * sizeof(int *)), i = 0;
    *returnSize = numRows;
    *returnColumnSizes = (int *)malloc(numRows * sizeof(int));
    for (;i < numRows; i++) {
        ans[i] = (int *)malloc((i + 3) * sizeof(int));
        ans[i][0] = 0;
        ans[i][1] = 1;
        ans[i][i + 1] = 1;
        ans[i][i + 2] = 0;
        for (int j = 2; j <= i; j++) {
            ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
            /* ans[2][2] = ans[1][1] + ans[1][2];
             * ans[3][2] = ans[2][1] + ans[2][2];
             * ans[3][3] = ans[2][2] + ans[2][3];
             * ans[4][2] = ans[3][1] + ans[3][2];
             * ans[4][3] = ans[3][2] + ans[3][3];
             * ans[4][4] = ans[3][3] + ans[3][4];
             * ...
             */
        }
        (*returnColumnSizes)[i] = i + 1;
        if (i)  ans[i - 1]++;
    }
    ans[i - 1]++;

    return ans;
}
