#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* getBiggestThree(int** grid, int gridSize, int* gridColSize, int* returnSize);
void insert(int *arr, int num);

int main() {
    int resSize = 0;
    int* res1 = getBiggestThree(
        (int*[]){
            (int[]){3, 4, 5, 1, 3},
            (int[]){3, 3, 4, 2, 3},
            (int[]){20, 30, 200, 40, 10},
            (int[]){1, 5, 5, 4, 1},
            (int[]){4, 3, 2, 2, 5}
        }, 
        5, 
        (int[]){5, 5, 5, 5, 5}, 
        &resSize);
    printf("[");
    for (int i = 0; i < resSize; i++) {
        printf("%d", res1[i]);
        if (i < resSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    int* res2 = getBiggestThree(
        (int*[]){
            (int[]){1, 2, 3},
            (int[]){4, 5, 6},
            (int[]){7, 8, 9}
        }, 
        3, 
        (int[]){3, 3, 3}, 
        &resSize);
    printf("[");
    for (int i = 0; i < resSize; i++) {
        printf("%d", res2[i]);
        if (i < resSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    int* res3 = getBiggestThree(
        (int*[]){(int[]){7, 7, 7}}, 
        1, 
        (int[]){3}, 
        &resSize);
    printf("[");
    for (int i = 0; i < resSize; i++) {
        printf("%d", res3[i]);
        if (i < resSize - 1) {
            printf(", ");
        }
    }
    printf("]\n");

    free(res1);
    free(res2);
    free(res3);
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getBiggestThree(int** grid, int gridSize, int* gridColSize, int* returnSize) {
    int *res = (int *)malloc(3 * sizeof(int));
    for (int i = 0; i < 3; i++) {
        res[i] = -1;
    }
    
    bool shouldStop = false;
    for (int i = 0; !shouldStop; i++) {
        shouldStop = true;
        for (int x = 0; x + 2 * i < gridSize; x++) {
            for (int y = i, sum = 0; y + i < gridColSize[x]; y++) {
                sum = grid[x][y];
                for (int j = 1; j <= i; j++) {
                    sum += (grid[x + j][y + j] + grid[x + j][y - j]);
                }
                for (int j = i + 1; j < 2 * i; j++) {
                    sum += (grid[x + j][y + 2 * i - j] + grid[x + j][y - 2 * i + j]);
                }
                if (i) {
                    sum += grid[x + 2 * i][y];
                }
                insert(res, sum);
                shouldStop = false;
            }
        }
    }
    *returnSize = 0;
    for (int i = 0; i < 3; i++) {
        if (res[i] > -1) {
            (*returnSize)++;
        }
    }
    return res;
}

void insert(int *arr, int num) {
    if (num == arr[0] || num == arr[1] || num == arr[2]) {
        return;
    }
    if (num > arr[0]) {
        arr[2] = arr[1];
        arr[1] = arr[0];
        arr[0] = num;
    }
    else if (num > arr[1]) {
        arr[2] = arr[1];
        arr[1] = num;
    }
    else if (num > arr[2]) {
        arr[2] = num;
    }
}
