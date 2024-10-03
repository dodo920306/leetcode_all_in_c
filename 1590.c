#include <stdio.h>
#include "uthash/include/uthash.h"

struct mapIntInt {
    int key, val;
    UT_hash_handle hh;
};

int minSubarray(int *nums, int numsSize, int p);

int minSubarray(int *nums, int numsSize, int p)
{
    int res = numsSize, target = 0;
    struct mapIntInt *map = NULL, *iter;

    for (int i = 0; i < numsSize; i++)
        target = (target + nums[i]) % p;

    if (!target)    return 0;

    iter = (struct mapIntInt *)malloc(sizeof(struct mapIntInt));
    if (!iter)  return -1;
    iter->key = 0;
    iter->val = -1;
    HASH_ADD_INT(map, key, iter);

    for (int i = 0, currentSum = 0, needed = 0, newLength = 0; i < numsSize; i++) {
        currentSum = (currentSum + nums[i]) % p;
        needed = (currentSum - target + p) % p;

        HASH_FIND_INT(map, &needed, iter);
        if (iter) {
            newLength = i - iter->val;
            if (newLength < res)    res = newLength;
        }

        HASH_FIND_INT(map, &currentSum, iter);
        if (!iter) {
            iter = (struct mapIntInt *)malloc(sizeof(struct mapIntInt));
            if (!iter)  return -1;
            iter->key = currentSum;
            HASH_ADD_INT(map, key, iter);
        }
        iter->val = i;
    }

    iter = map;
    for (struct mapIntInt *nextMap; iter; iter = nextMap) {
        nextMap = iter->hh.next;
        free(iter);
    }

    return res == numsSize ? -1 : res;
}

int main()
{
    int nums[] = {3, 1, 4, 2};
    printf("%d\n", minSubarray(nums, 4, 6));
    return 0;
}
