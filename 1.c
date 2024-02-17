#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10000

struct hashnode {
    int key, value;
    struct hashnode *next, *prev;
};

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *res = (int *)calloc(2, sizeof(int));
    if (!res) {
        perror("Error");
        return NULL;
    }
    struct hashnode **table = (struct hashnode **)calloc(HASH_SIZE, sizeof(struct hashnode *));
    if (!table) {
        perror("Error");
        return res;
    }
    for (int i = 0, complement; i < numsSize; i++) {
        /**
         * try find complement first
         * If nums[i] is one of elements in the answer pair
         * that shows up in the array later than the other,
         * it must be able to find its complement here.
         */
        complement = target - nums[i];
        struct hashnode *iter1 = table[abs(complement) % HASH_SIZE];
        while (iter1) {
            /* try to find the complement in the collision list */
            if (iter1->value == complement && iter1->key != i) {
                /* This is where we return the result. */
                *returnSize = 2;
                res[0] = iter1->key;
                res[1] = i;
                goto stop;
            }
            iter1 = iter1->next;
        }
        /**
         * If we can't find the complement, we insert nums[i] in the table
         * to allow others to find it later.
         * Remains won't always be positive in C.
         * Instead, it depends on whether the dividend is positive,
         * so we deal with the dividend with abs() to provide indices.
         * iter2 is a pointer to the pointer in the table to make
         * values of pointers in the table changeable.
         */
        struct hashnode **iter2 = &table[abs(nums[i]) % HASH_SIZE];
        if (*iter2) {
            /**
             * handle collisions
             * iter2 stops before NULL to be preserved as the prev pointer.
             * This if statement can be eliminated to enhance performance
             * if we don't need prev pointers
             * However, I don't want that since they're needed for later memory release.
             */
            while (((*iter2)->next))  iter2 = &((*iter2)->next);

            ((*iter2)->next) = (struct hashnode *)malloc(sizeof(struct hashnode));
            if (!((*iter2)->next)) {
                perror("Error");
                goto stop;
            }
            ((*iter2)->next)->key = i;
            ((*iter2)->next)->value = nums[i];
            ((*iter2)->next)->next = NULL;
            ((*iter2)->next)->prev = (*iter2);
        }
        else {
            (*iter2) = (struct hashnode *)malloc(sizeof(struct hashnode));
            if (!(*iter2)) {
                perror("Error");
                goto stop;
            }
            (*iter2)->key = i;
            (*iter2)->value = nums[i];
            (*iter2)->next = NULL;
            (*iter2)->prev = NULL;
        }
    }
    stop:
    for (int i = 0, index; i < numsSize; i++) {
        index = abs(nums[i]) % HASH_SIZE;
        struct hashnode *iter = table[index];
        if (iter) {
            while (iter->next && iter->next->next)  iter = iter->next;
            /* use prev pointers to release the list elements */
            while (iter->prev) {
                free(iter->next);
                iter = iter->prev;
            }
            free(iter->next);
        }
        free(iter);
        /* make list head NULL to prevent there are elements later trying to free the same list */
        table[index] = NULL;
    }
    free(table);
    return res;
}

int main()
{
    int nums[] = {2,7,11,15}, returnSize, *res = twoSum(nums, 4, 9, &returnSize);
    for (int i = 0; i < returnSize; i++)
        printf("%d ", res[i]);
    free(res);
    return 0;
}
