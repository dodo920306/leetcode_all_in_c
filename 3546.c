#include <stdio.h>
#include <stdbool.h>

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize);
long getRowSum(int* row, int size);
long getColumnSum(int** grid, int gridSize, int column);

int main() {
    printf(canPartitionGrid(
        (int*[]){(int[]){1, 4}, (int[]){2, 3}}, 
        2, 
        (int[]){2, 2}) ? "true\n" : "false\n");
    printf(canPartitionGrid(
        (int*[]){(int[]){1, 3}, (int[]){2, 4}}, 
        2, 
        (int[]){2, 2}) ? "true\n" : "false\n");
    return 0;
}

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    long gridSum = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            gridSum += grid[i][j];
        }
    }
    if (gridSum % 2) {
        return false;
    }
    gridSum >>= 1;

    long prefixSum = 0;
    for (int i = 0; prefixSum < gridSum && i < gridSize; i++) {
        prefixSum += getRowSum(grid[i], gridColSize[i]);
        if (prefixSum == gridSum) {
            return true;
        }
    }
    prefixSum = 0;
    for (int i = 0; prefixSum < gridSum && i < gridColSize[0]; i++) {
        prefixSum += getColumnSum(grid, gridSize, i);
        if (prefixSum == gridSum) {
            return true;
        }
    }
    return false;
}

long getRowSum(int* row, int size) {
    long res = row[0];
    for (int i = 1; i < size; i++) {
        res += row[i];
    }
    return res;
}

long getColumnSum(int** grid, int gridSize, int column) {
    long res = grid[0][column];
    for (int i = 1; i < gridSize; i++) {
        res += grid[i][column];
    }
    return res;
}
