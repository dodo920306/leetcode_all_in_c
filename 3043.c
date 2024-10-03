#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "uthash/include/uthash.h"

struct set {
    int key;
    UT_hash_handle hh;
};

bool isIn(struct set *set, int k);
int numOfDigits(int k);
int longestCommonPrefix(int *arr1, int arr1Size, int *arr2, int arr2Size);

bool isIn(struct set *set, int k)
{
    struct set *s;
    HASH_FIND_INT(set, &k, s);
    return !!s;
}

int numOfDigits(int k)
{
    int res = 0;
    while (k) {
        res++;
        k /= 10;
    }
    return res;
}

int longestCommonPrefix(int *arr1, int arr1Size, int *arr2, int arr2Size)
{
    struct set *set = NULL, *iter, *tmp;
    int res = 0;

    if (arr2Size < arr1Size)
        return longestCommonPrefix(arr2, arr2Size, arr1, arr1Size);
    
    for (int i = 0; i < arr1Size; i++)
        while (arr1[i] && !isIn(set, arr1[i])) {
            iter = (struct set *)malloc(sizeof(struct set));
            if (!iter) {
                fprintf(stderr, "Error: Memory Allocation Failed.");
                return -1;
            }
            iter->key = arr1[i];
            HASH_ADD_INT(set, key, iter);
            arr1[i] /= 10;
        }

    for (int i = 0, _res; i < arr2Size; i++) {
        while (arr2[i] && !isIn(set, arr2[i]))
            arr2[i] /= 10;

        _res = numOfDigits(arr2[i]);
        if (res < _res)
            res = _res;
    }

    HASH_ITER(hh, set, iter, tmp) {
        free(iter);
    }
    return res;
}

int main()
{
    int arr1[] = {1, 10, 100}, arr2[] = {1000};
    printf("%d\n", longestCommonPrefix(arr1, 3, arr2, 1));
    return 0;
}
