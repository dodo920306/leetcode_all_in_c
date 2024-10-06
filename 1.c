#include <stdio.h>
#include "uthash/include/uthash.h"

struct mapIntInt {
    int key, val;
    UT_hash_handle hh;
};

int *twoSum(int *, int, int, int *);
void printIntArray(int *, int);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    struct mapIntInt *map = NULL, *iter = NULL, *tmp = NULL;
    int *res = (int *)malloc(sizeof(int) << 1);
    *returnSize = 0;
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    for (int i = 0, component = 0; i < numsSize; i++) {
        component = target - nums[i];
        HASH_FIND_INT(map, &component, iter);
        if (iter) {
            *returnSize = 2;
            res[0] = iter->val;
            res[1] = i;
            break;
        }
        iter = (struct mapIntInt *)malloc(sizeof(struct mapIntInt));
        if (!iter) {
            fprintf(stderr, "Error: Memory Allocation Failed.");
            break;
        }
        iter->key = nums[i];
        iter->val = i;
        HASH_ADD_INT(map, key, iter);
    }

    HASH_ITER(hh, map, iter, tmp) {
        free(iter);
    }
    return res;
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
    int nums[] = {2,7,11,15}, returnSize, *res = twoSum(nums, 4, 9, &returnSize);
    printIntArray(res, returnSize);
    free(res);
    return 0;
}
