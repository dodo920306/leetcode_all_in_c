#include <stdio.h>
#include "uthash/include/uthash.h"

struct mapIntInt {
    int key, val;
    UT_hash_handle hh;
};

int cmp(const struct mapIntInt *, const struct mapIntInt *);
int *frequencySort(int *, int, int *);
void printIntArray(int *, int);

int cmp(const struct mapIntInt *a, const struct mapIntInt *b)
{
    if (a->val == b->val)
        return b->key - a->key;
    return a->val - b->val;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *frequencySort(int *nums, int numsSize, int *returnSize)
{
    struct mapIntInt *map = NULL, *iter = NULL, *tmp = NULL;
    *returnSize = 0;
    for (int i = 0; i < numsSize; i++) {
        HASH_FIND_INT(map, &(nums[i]), iter);
        if (iter) {
            iter->val++;
            continue;
        }
        iter = (struct mapIntInt *)malloc(sizeof(struct mapIntInt));
        if (!iter) {
            fprintf(stderr, "Error: Memory Allocation Failed.");
            return NULL;
        }
        iter->key = nums[i];
        iter->val = 1;
        HASH_ADD_INT(map, key, iter);
    }
    HASH_SORT(map, cmp);
    HASH_ITER(hh, map, iter, tmp) {
        while (iter->val) {
            nums[(*returnSize)++] = iter->key;
            iter->val--;
        }
        free(iter);
    }
    return nums;
}

void printIntArray(int *arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%d, ", arr[i]);
    }
    if (arrSize >= 0)
        printf("%d]\n", arr[arrSize]);
    else
        printf("]\n");
}

int main()
{
    int *nums = (int *)malloc(6 * sizeof(int)), returnSize = 0, *res = NULL;
    if (!nums) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return -1;
    }
    nums[0] = 1;
    nums[1] = 1;
    nums[2] = 2;
    nums[3] = 2;
    nums[4] = 2;
    nums[5] = 3;
    res = frequencySort(nums, 6, &returnSize);
    printIntArray(res, returnSize);
    free(res);
    return 0;
}
