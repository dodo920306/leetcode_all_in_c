#include <stdio.h>
#include <stdlib.h>

#define BIGGEST_NEGATIVE_INTEGER -1
#define __max(a,b) (((a) > (b)) ? (a) : (b))

int cherryPickup(int** grid, int gridSize, int* gridColSize);

int cherryPickup(int** grid, int gridSize, int* gridColSize)
{
    int ***dp = (int ***)malloc(gridSize * sizeof(int **)), res = BIGGEST_NEGATIVE_INTEGER;
    if (!dp)    return BIGGEST_NEGATIVE_INTEGER;
    for (int i = 0; i < gridSize; i++) {
        dp[i] = (int **)malloc(*gridColSize * sizeof(int *));
        if (!dp[i])    return BIGGEST_NEGATIVE_INTEGER;
        for (int j = 0; j < *gridColSize; j++) {
            dp[i][j] = (int *)malloc(*gridColSize * sizeof(int));
            if (!dp[i][j])    return BIGGEST_NEGATIVE_INTEGER;
            for (int k = 0; k < *gridColSize; k++)
                dp[i][j][k] = BIGGEST_NEGATIVE_INTEGER;
        }
    }

    /**
     * In the first row,
     * if *gridColSize is 1, the 2 robots is in fact in the same column.
     * Thus, only the number of cherries on one grid is counted in.
     */
    dp[0][0][(*gridColSize) - 1] = **grid;
    if (*gridColSize > 1)   dp[0][0][*gridColSize - 1] += (*grid)[*gridColSize - 1];

    /* for each row */
    for (int i = 1; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++) {
            for (int k = 0; k < *gridColSize; k++) {
                /**
                 * check if the upper one is reachable.
                 * If the value is -1, it will be 0xFFFFFFFF.
                 * Thus, ~it will be 0x00000000, 
                 * so it won't pass the if statement.
                 */
                if (~dp[i - 1][j][k]) {
                    for (int dj = -1, _j = 0; dj < 2; dj++) {
                        _j = j + dj;
                        for (int dk = -1, _k = 0; dk < 2; dk++) {
                            _k = k + dk;
                            if (_j >= 0 && _j < *gridColSize && _k >= 0 && _k < *gridColSize) {
                                if (_j == _k)   dp[i][_j][_k] = dp[i - 1][j][k] + grid[i][_j];
                                else    dp[i][_j][_k] = __max(dp[i][_j][_k], dp[i - 1][j][k] + grid[i][_j] + grid[i][_k]);
                                res = __max(res, dp[i][_j][_k]);
                            }
                        }
                    }
                }
            }
        }
    }

    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < *gridColSize; j++)
            free(dp[i][j]);
        free(dp[i]);
    }
    free(dp);

    return res;
}

int main()
{
    int **grid= (int **)malloc(4 * sizeof(int *)), gridColSize[4] = {3,3,3,3};
    if (!grid)    return 1;
    for (int i = 0; i < 4; i++) {
        grid[i] = (int *)malloc(3 * sizeof(int));
        if (!grid[i])    return 2;
    }
    grid[0][0] = 3;
    grid[0][1] = 1;
    grid[0][2] = 1;
    grid[1][0] = 2;
    grid[1][1] = 5;
    grid[1][2] = 1;
    grid[2][0] = 1;
    grid[2][1] = 5;
    grid[2][2] = 5;
    grid[3][0] = 2;
    grid[3][1] = 1;
    grid[3][2] = 1;
    
    printf("%d\n", cherryPickup(grid, 4, gridColSize));

    for (int i = 0; i < 4; i++)
        free(grid[i]);
    free(grid);
    return 0;
}
