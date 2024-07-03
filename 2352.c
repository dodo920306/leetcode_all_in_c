#include <stdio.h>
#include <stdlib.h>

#define MOD 10781

int equalPairs(int **grid, int gridSize, int *gridColSize);

int equalPairs(int **grid, int gridSize, int *gridColSize)
{
    /**
     * grid is a n x n square matrix,
     * so gridSize equals to every element in gridColSize.
     */
    int res = 0, *table1, *table2;
    if (!(table1 = (int *)malloc(gridSize * sizeof(int))) || !(table2 = (int *)malloc(gridSize * sizeof(int))))
        return -1;
    for (int i = 0; i < gridSize; i++)
        for (int j = 0, multiplier; j < gridSize; j++) {
            /**
             * Adding 1 is to not ignore the first element of each row/column.
             * Modulo is to prevent overflow and increase randomness.
             * Using square of (j + 1) is to amplify difference between
             * elements with the same value in different positions.
             */
            multiplier = (j + 1) * (j + 1) % MOD;
            table1[i] += grid[i][j] * multiplier % MOD;
            table2[i] += grid[j][i] * multiplier % MOD;
        }
    
    for (int i = 0, j; i < gridSize; i++) {
        j = 0;
        while (j < gridSize) {
            if (table1[i] == table2[j])
                res++;
            j++;
        }
    }
    free(table1);
    free(table2);
    return res;
}

int main()
{
    int gridColSize[] = {4, 4, 4, 4}, row0[] = {3, 1, 2, 2}, row1[] = {1, 4, 4, 5}, row2[] = {2, 4, 2, 2}, row3[] = {2, 4, 2, 2}, *grid[] = {row0, row1, row2, row3};
    printf("%d\n", equalPairs(grid, 4, gridColSize));
    return 0;
}
