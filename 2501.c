#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uthash.h"

struct IntSet {
    int key;
    UT_hash_handle hh;
};

void addIntToSet(struct IntSet **self, int val);
bool isInIntSet(struct IntSet *self, int val);
void clearIntSet(struct IntSet **self);
int longestSquareStreak(int *nums, int numsSize);

int main() {
    int nums[] = {4, 3, 6, 16, 8, 2};
    printf("%d\n", longestSquareStreak(nums, 6));
    return 0;
}

void addIntToSet(struct IntSet **self, int val)
{
    struct IntSet *element = NULL;
    HASH_FIND_INT(*self, &val, element);
    if (element)    return;
    element = (struct IntSet *)malloc(sizeof(struct IntSet));
    element->key = val;
    HASH_ADD_INT(*self, key, element);
}

bool isInIntSet(struct IntSet *self, int val)
{
    struct IntSet *element = NULL;
    HASH_FIND_INT(self, &val, element);
    return !!element;
}

void clearIntSet(struct IntSet **self) {
    struct IntSet *iter, *tmp;
    HASH_ITER(hh, *self, iter, tmp) {
        HASH_DEL(*self, iter);
        free(iter);
    }
}

int longestSquareStreak(int *nums, int numsSize)
{
    int res = -1, cur = 0;
    struct IntSet *uniqueNumbers = NULL;
    for (int i = 0; i < numsSize; i++) {
        /* Put every element into the set */
        addIntToSet(&uniqueNumbers, nums[i]);
    }

    for (long long i = 0, cur, tmp; i < numsSize; i++) {
        /* the current length of streak */
        cur = 0;
        tmp = nums[i];

        do {
            /**
             * If tmp^2 exists in the set,
             * add 1 to the current length of streak.
             */
            cur++;
            if (tmp * tmp > 1e5) {
                break;
            }
            tmp *= tmp;
        } while (isInIntSet(uniqueNumbers, tmp));

        /* update the longest length of streak */
        if (res < cur)  res = cur;
    }
    clearIntSet(&uniqueNumbers);
    return res > 1 ? res : -1;
}
