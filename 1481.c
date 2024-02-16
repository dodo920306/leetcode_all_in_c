#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

/**
 * The current solution still bounded by qsort(), which is O(n^2).
 * A O(nlogn) solution will be appreciated.
 */
int findLeastNumOfUniqueInts(int *arr, int arrSize, int k)
{
    int uni = 0, i = 0, sign = ((sizeof(int) << 3) - 1);

    /* sort arr to gather same elements. */
    qsort(arr, arrSize, sizeof(int), cmp);
    for (int key; i < arrSize; uni++) {
        key = arr[i];
        /* We use the original array to store frequencies to save space. */
        arr[uni] = 1;
        /* keep counting until a new item shows up */
        for (i++; i < arrSize && arr[i] == key; i++)    arr[uni]++;
    }

    /* sort by frequency. */
    qsort(arr, uni, sizeof(int), cmp);
    for (i = 0; k > 0; i++)
        /* count how many more elements need to be deleted to achieve k removals */
        k -= arr[i];
    /**
     * The number of the rest elements is the result.
     * If k is negative, the final elements that are deleted shouldn't be all be deleted
     * i.e. some of them remains in arr after removals
     * i.e. it counts as one of the final unique integers.
     * Thus, here we add 1 back to the result.
     */
    return k >> sign ? uni - i + 1 : uni - i;
}

int main()
{
    int arr[] = {4,3,1,1,3,3,2};
    printf("%d", findLeastNumOfUniqueInts(arr, 7, 3));
    return 0;
}
