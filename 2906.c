#include <stdio.h>
#include <stdlib.h>

#define MOD 12345

int** constructProductMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes);
int multiplyWithMod(int a, int b);

int main() {
    int returnSize1 = 0;
    int* returnColumnSizes1 = NULL;
    int** res1 = constructProductMatrix(
        (int*[]){(int[]){1, 2}, (int[]){3, 4}}, 
        2, 
        (int[]){2, 2},
        &returnSize1,
        &returnColumnSizes1);
    printf("[\n");
    for (int i = 0; i < returnSize1; i++) {
        printf("    [");
        for (int j = 0; j < returnColumnSizes1[i] - 1; j++) {
            printf("%d, ", res1[i][j]);
        }
        printf("%d", res1[i][returnColumnSizes1[i] - 1]);
        printf(i == returnSize1 - 1 ? "]\n" : "],\n");
    }
    printf("],\n");

    int returnSize2 = 0;
    int* returnColumnSizes2 = NULL;
    int** res2 = constructProductMatrix(
        (int*[]){(int[]){12345}, (int[]){2}, (int[]){1}}, 
        3, 
        (int[]){1, 1, 1},
        &returnSize2,
        &returnColumnSizes2);
    printf("[\n");
    for (int i = 0; i < returnSize2; i++) {
        printf("    [");
        for (int j = 0; j < returnColumnSizes2[i] - 1; j++) {
            printf("%d, ", res2[i][j]);
        }
        printf("%d", res2[i][returnColumnSizes2[i] - 1]);
        printf(i == returnSize2 - 1 ? "]\n" : "],\n");
    }
    printf("]\n");
    return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** constructProductMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int prefixProduct = 1;
    int** res = (int**)malloc(gridSize * sizeof(int *));
    for (int i = gridSize - 1; i >= 0; i--) {
        res[i] = (int*)malloc(gridColSize[i] * sizeof(int));
        res[i][gridColSize[i] -  1] = (i == gridSize - 1) ? 1 : multiplyWithMod(res[i + 1][0], grid[i + 1][0]);

        for (int j = gridColSize[i] - 2; j >= 0; j--) {
            res[i][j] = multiplyWithMod(res[i][j + 1], grid[i][j + 1]);
        }
    }

    *returnColumnSizes = (int*)malloc(gridSize * sizeof(int));
    for (int i = 0; i < gridSize; i++) {
        (*returnColumnSizes)[i] = gridColSize[i];
        for (int j = 0; j < gridColSize[i]; j++) {
            res[i][j] = multiplyWithMod(prefixProduct, res[i][j]);
            prefixProduct = multiplyWithMod(prefixProduct, grid[i][j]);
        }
    }

    *returnSize = gridSize;
    return res;
}

int multiplyWithMod(int a, int b) {
    return (a * (b % MOD)) % MOD;
}
