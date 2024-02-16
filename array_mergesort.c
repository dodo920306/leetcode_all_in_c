#include <stdio.h>

void copy(int *a, int *b, int size)
{
    while (size--)    *a++ = *b++;
}

/* mergesort is used here to reduce time since qsort() takes O(n^2). */
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

int main()
{
    int arr[] = {4,3,1,1,3,3,2};
    merge(arr, 0, 6);
    for (int i = 0; i < 7; i++) printf("%d ", arr[i]);
    return 0;
}
