#include <stdio.h>
#include <stdlib.h>

void copy(int *a, int *b, int size)
{
    while (size--)    *a++ = *b++;
}

/* merge sort is used here to reduce time since qsort() takes O(n^2). */
void merge(int *arr, int left, int right)
{
    if (left == right)  return;

    int m = (right + left) / 2, l = 0, r = 0, lsize = m - left + 1, rsize = right - m, r1[lsize], r2[rsize];

    merge(arr, left, m);
    m++;
    merge(arr, m, right);

    copy(r1, arr + left, (lsize));
    copy(r2, arr + m, (rsize));

    /* merge 2 sorted array */
    while (l < lsize && r < rsize)  arr[left++] = r1[l] < r2[r] ? r1[l++] : r2[r++];
    arr += left;
    /* One of (lsize - l) and (rsize - r) is 0, so the sum of them is the number of rest elements. */
    lsize -= l;
    rsize -= r;
    copy(arr, (lsize ? r1 + l : r2 + r), lsize + rsize);
}

int findLeastNumOfUniqueInts(int *arr, int arrSize, int k)
{
    int uni = 0, i = 0, sign = ((sizeof(int) << 3) - 1);

    /* sort arr to gather same elements. */
    merge(arr, 0, arrSize - 1);
    for (int key; i < arrSize; uni++) {
        key = arr[i];
        /* We use the original array to store frequencies to save space. */
        arr[uni] = 1;
        /* keep counting until a new item shows up */
        for (i++; i < arrSize && arr[i] == key; i++)    arr[uni]++;
    }

    /* sort by frequency. */
    merge(arr, 0, uni - 1);
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
