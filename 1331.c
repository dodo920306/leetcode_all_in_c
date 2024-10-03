#include <stdio.h>
#include <stdlib.h>
#include "uthash/include/uthash.h"

struct mapIntInt {
    int key, val;
    UT_hash_handle hh;
};

void printIntArray(int *arr, int arrSize);
int cmp(const void *a, const void *b);
struct mapIntInt *getOrCreate(struct mapIntInt **map, int key);
void freeMap(struct mapIntInt **map);
int *arrayRankTransform(int *arr, int arrSize, int *returnSize);

void printIntArray(int *arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[arrSize]);
}

int cmp(const void *a, const void *b)
{
    return ((struct mapIntInt *)a)->key - ((struct mapIntInt *)b)->key;
}

struct mapIntInt *getOrCreate(struct mapIntInt **map, int key)
{
    struct mapIntInt *findResult = NULL;
    HASH_FIND_INT(*map, &key, findResult);
    if (findResult) return findResult;
    
    findResult = (struct mapIntInt *)malloc(sizeof(struct mapIntInt));

    if (!(findResult)) {
        fprintf(stderr, "Error: Memory Allocation Error.");
        return NULL;
    }

    findResult->key = key;
    findResult->val = 0;
    HASH_ADD_INT(*map, key, findResult);
    return findResult;
}

void freeMap(struct mapIntInt **map)
{
    for (struct mapIntInt *iter = *map, *nextMap; iter; iter = nextMap) {
        nextMap = iter->hh.next;
        free(iter);
    }
    free(map);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *arrayRankTransform(int *arr, int arrSize, int *returnSize)
{
    struct mapIntInt **ranks = (struct mapIntInt **)calloc(1, sizeof(struct mapIntInt *));
    int rank = 1;

    if (!ranks) return NULL;
    *ranks = NULL;

    for (int i = 0; i < arrSize; i++)
        getOrCreate(ranks, arr[i]);

    HASH_SORT(*ranks, cmp);

    for (struct mapIntInt *iter = *ranks; iter; iter = iter->hh.next) {
        iter->val = rank;
        rank++;
    }

    for (int i = 0; i < arrSize; i++)
        arr[i] = getOrCreate(ranks, arr[i])->val;

    freeMap(ranks);

    *returnSize = arrSize;
    return arr;
}

int main()
{
    int *arr = (int *)malloc(4 * sizeof(int)), returnSize = 0;
    if (!arr) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return -1;
    }

    arr = arrayRankTransform(arr, 4, &returnSize);
    printIntArray(arr, returnSize);
    free(arr);
    return 0;
}
