#include <stdio.h>
#include <stdlib.h>

int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes);

int main()
{
    int groupSizes[7] = {3, 3, 3, 3, 3, 1, 3}, groupSizesSize = 7, returnSize, *returnColumnSizes;
    int **ans = groupThePeople(groupSizes, groupSizesSize, &returnSize, &returnColumnSizes);
    for (int i = 0; i < returnSize; i++)
    {
        for (int j = 0; j < returnColumnSizes[i]; j++)
        {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
    
}

int** groupThePeople(int* groupSizes, int groupSizesSize, int* returnSize, int** returnColumnSizes)
{
    int **group = (int **)malloc(groupSizesSize * sizeof(int *)), *top = (int *)malloc(groupSizesSize * sizeof(int)), **ans, amount = 0;
    for (int i = 0; i < groupSizesSize; i++) {
        group[i] = (int *)malloc(groupSizesSize * sizeof(int));
        top[i] = 0;
    }
    
    for (int i = 0; i < groupSizesSize; i++) {
        int tmp = groupSizes[i] - 1;
        group[tmp][top[tmp]] = i;
        top[tmp]++;
    }

    for (int i = 0; i < groupSizesSize; i++) {
        amount += top[i] / (i + 1);
    }

    ans = (int **)malloc(amount * sizeof(int *));
    *returnSize = amount;
    *returnColumnSizes = (int *)malloc(amount * sizeof(int));
    amount = 0;

    for (int i = 0; amount < *returnSize && i < groupSizesSize; i++) {
        if (top[i]) {
            int tmp = i + 1;
            for (int j = 0; j < top[i] / tmp; j++) {
                ans[amount] = (int *)malloc(tmp * sizeof(int));
                (*returnColumnSizes)[amount] = tmp;
                for (int k = 0; k <= i; k++) {
                    ans[amount][k] = group[i][k + j * tmp];
                }
                amount++;
            }
        }
    }
    return ans;
}
