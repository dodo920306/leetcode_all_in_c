#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash.h"

struct Position {
    int x;
    int y;
};

struct MapValueToPositionsEntry {
    int key;
    struct Position* positions;
    int size;
    int capacity;
    UT_hash_handle hh;
};

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize);
long getRowSum(int* row, int size);
long getColumnSum(int** grid, int gridSize, int column);
bool find(int** grid, long target, int up, int down, int left, int right);
void putPosition(int key, int x, int y);
void freeMap();

struct MapValueToPositionsEntry* map = NULL;

int main() {
    printf(canPartitionGrid(
        (int*[]){(int[]){1, 4}, (int[]){2, 3}}, 
        2, 
        (int[]){2, 2}) ? "true\n" : "false\n");
    printf(canPartitionGrid(
        (int*[]){(int[]){1, 2}, (int[]){3, 4}}, 
        2, 
        (int[]){2, 2}) ? "true\n" : "false\n");
    printf(canPartitionGrid(
        (int*[]){(int[]){1, 2, 4}, (int[]){2, 3, 5}}, 
        2, 
        (int[]){3, 3}) ? "true\n" : "false\n");
    return 0;
}

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[0]; j++) {
            putPosition(grid[i][j], i, j);
        }
    }

    long* prefixRowSum = (long*)malloc(gridSize * sizeof(long));
    prefixRowSum[0] = getRowSum(grid[0], gridColSize[0]);
    for (int i = 1; i < gridSize; i++) {
        prefixRowSum[i] = prefixRowSum[i - 1] + getRowSum(grid[i], gridColSize[i]);
    }
    long gridSum = prefixRowSum[gridSize - 1];

    long* prefixColumnSum = (long*)malloc(gridColSize[0] * sizeof(long));
    prefixColumnSum[0] = getColumnSum(grid, gridSize, 0);
    for (int i = 1; i < gridColSize[0]; i++) {
        prefixColumnSum[i] = prefixColumnSum[i - 1] + getColumnSum(grid, gridSize, i);
    }

    long target = 0;
    for (int i = 0; i < gridSize - 1; i++) {
        target = 2 * prefixRowSum[i] - gridSum;
        if (find(grid, target, 0, i + 1, 0, gridColSize[i])) {
            freeMap();
            free(prefixRowSum);
            free(prefixColumnSum);
            return true;
        }
    }

    for (int i = gridSize - 1; i > 0; i--) {
        target = gridSum - 2 * prefixRowSum[i - 1];
        if (find(grid, target, i, gridSize, 0, gridColSize[i])) {
            freeMap();
            free(prefixRowSum);
            free(prefixColumnSum);
            return true;
        }
    }

    for (int i = 0; i < gridColSize[0] - 1; i++) {
        target = 2 * prefixColumnSum[i] - gridSum;
        if (find(grid, target, 0, gridSize, 0, i + 1)) {
            freeMap();
            free(prefixRowSum);
            free(prefixColumnSum);
            return true;
        }
    }

    for (int i = gridColSize[0] - 1; i > 0; i--) {
        target = gridSum - 2 * prefixColumnSum[i - 1];
        if (find(grid, target, 0, gridSize, i, gridColSize[0])) {
            freeMap();
            free(prefixRowSum);
            free(prefixColumnSum);
            return true;
        }
    }

    freeMap();
    free(prefixRowSum);
    free(prefixColumnSum);
    return false;
}

bool find(int** grid, long target, int up, int down, int left, int right) {
    if (!target) {
        return true;
    }
    if (target < 0) {
        return false;
    }
    if (target > 100000) {
        return false;
    }
    if (down - up == 1) {
        return grid[up][left] == target || grid[up][right - 1] == target;
    }
    if (right - left == 1) {
        return grid[up][left] == target || grid[down - 1][left] == target;
    }

    struct MapValueToPositionsEntry* entry;
    int key = (int)target;

    HASH_FIND_INT(map, &key, entry);
    if (!entry) return false;

    for (int i = 0; i < entry->size; i++) {
        int x = entry->positions[i].x;
        int y = entry->positions[i].y;

        if (x >= up && x < down && y >= left && y < right) {
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

void putPosition(int key, int x, int y) {
    struct MapValueToPositionsEntry* entry;

    HASH_FIND_INT(map, &key, entry);

    if (!entry) {
        entry = (struct MapValueToPositionsEntry*)malloc(sizeof(struct MapValueToPositionsEntry));
        entry->key = key;
        entry->size = 0;
        entry->capacity = 4;
        entry->positions = (struct Position*)malloc(entry->capacity * sizeof(struct Position));

        HASH_ADD_INT(map, key, entry);
    }

    if (entry->size == entry->capacity) {
        entry->capacity <<= 1;
        entry->positions = realloc(entry->positions, entry->capacity * sizeof(struct Position));
    }

    entry->positions[entry->size++] = (struct Position){x, y};
}

void freeMap() {
    struct MapValueToPositionsEntry *cur, *tmp;
    HASH_ITER(hh, map, cur, tmp) {
        HASH_DEL(map, cur);
        free(cur->positions);
        free(cur);
    }
}
