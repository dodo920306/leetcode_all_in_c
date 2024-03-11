#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);ni
int *intersection(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize);

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *intersection(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize)
{
    int i = 0, j = 0, *res = (int *)malloc(((nums2Size > nums1Size) ? nums1Size : nums2Size) * sizeof(int));
    if (!res) {
        perror("Error");
        return NULL;
    }
    *returnSize = 0;

    qsort(nums1, nums1Size, sizeof(int), cmp);
    qsort(nums2, nums2Size, sizeof(int), cmp);
    while (i < nums1Size && j < nums2Size)
        if (nums1[i] > nums2[j])   j++;
        else {
            if ((nums1[i] == nums2[j]) && (!(*returnSize) || (nums1[i] != res[(*returnSize) - 1]))) 
                res[(*returnSize)++] = nums1[i];
            i++;
        }
    return res;
}

int main()
{
    int nums1[] = {4, 9, 5}, nums2[] = {9, 4, 9, 8, 4}, returnSize, *res = intersection(nums1, 3, nums2, 5, &returnSize);
    for (int i = 0; i < returnSize; i++)
        printf("%d ", res[i]);
    free(res);
    return 0;
}
