#include <stdio.h>
#include <stdbool.h>

#define cmp(a, b) a > b ? true : false

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n);

int main()
{
    int nums1[6] = {1, 2, 3, 0, 0 ,0}, nums2[3] = {2, 5, 6}, nums1Size = 6, m = 3, nums2Size = 3, n = 3;
    merge(nums1, nums1Size, m, nums2, nums2Size, n);
    int *end_ptr1 = nums1 + nums1Size, *run_ptr = nums1;
    while (run_ptr != end_ptr1) {
        printf("%d ", *run_ptr);
        run_ptr += 1;
    }
}

void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
    /* Sort from tail to head here so that inserted values won't cover the original values in nums1. */
    int *end_ptr1 = nums1 + m - 1, *end_ptr2 = nums2 + nums2Size - 1, *run_ptr = nums1 + nums1Size;
    while (end_ptr1 >= nums1 && end_ptr2 >= nums2) {
        if (cmp(*end_ptr1, *end_ptr2)) {
            *(--run_ptr) = *(end_ptr1--);
        }
        else {
            *(--run_ptr) = *(end_ptr2--);
        }
    }
    
    /* Don't need to care "end_ptr1 >= nums1" case because remain values are already in nums1.  */
    while (end_ptr2 >= nums2) {
        *(--run_ptr) = *(end_ptr2--);
    }
}
