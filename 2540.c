#include <stdio.h>

int getCommon(int *nums1, int nums1Size, int *nums2, int nums2Size);

int getCommon(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    int i = 0, j = 0;
    while (i < nums1Size && j < nums2Size)
        if (nums1[i] < nums2[j])    i++;
        else if (nums1[i] > nums2[j])   j++;
        else    return nums1[i];
    return -1;
}

int main()
{
    int nums1[] = {1, 2, 3, 6}, nums2[] = {2, 3, 4, 5};
    printf("%d", getCommon(nums1, 4, nums2, 4));
    return 0;
}
