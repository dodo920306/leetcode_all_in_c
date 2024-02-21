#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size);

double findMedianSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size)
{
    int *temp_ptr, temp, left = 0, right, total = nums1Size + nums2Size, half = total >> 1, i, j, left_A, right_A, left_B, right_B, sign = ((sizeof(int) << 3) - 1);
    if (nums2Size < nums1Size) {
        /* We want to make sure that nums1 is the shorter one, so we swap them if not. */
        temp_ptr = nums1;
        nums1 = nums2;
        nums2 = temp_ptr;
        temp = nums1Size;
        nums1Size = nums2Size;
        nums2Size = temp;
    }
    nums1Size--;
    nums2Size--;
    right = nums1Size;
    /* We call nums1 (the shorter one) as A and the other as B in the following description. */
    while (true) {
        /* We pretend that A[0] ~ A[i] are on the left hand size of the merged array. */
        i = floor((left + right) / 2.0);
        /**
         * We pretend that B[0] ~ B[j] are on the left hand size of the merged array.
         * Thus, half = (i + 1) + (j + 1).
         */
        j = half - i - 2;
        /**
         * Therefore, we can get the largest element from A 
         * on the left hand size of the merged array
         * is A[i].
         * If i is negative, no element from A will 
         * fall on the left hand size of the merged array.
         * In this case, 
         * left_A should be smaller right_B 'cause we can't lower left_A anymore, 
         * so we set it -infinity here.
         * The bounds for the other 3 variables are also used in the same logic.
         * Read the following statements to get more details.
         */
        left_A  = i >> sign ? INT_MIN : nums1[i];
        right_A = i < nums1Size ? nums1[i + 1] : INT_MAX;
        left_B  = j >> sign ? INT_MIN : nums2[j];
        right_B = j < nums2Size ? nums2[j + 1] : INT_MAX;

        if (left_A <= right_B && left_B <= right_A) {
            /**
             * Since A and B are sorted, 
             * we can safely say left_A < right_A no matter what.
             * Therefore, 
             * if left_A < right_B, left_A is smaller than most of the merged array.
             * The hypothesis is valid, 
             * A[0] ~ A[i] are on the left hand size of the merged array.
             * If B[0] ~ B[j] are also on the left hand size of the merged array,
             * since we keep half = (i + 1) + (j + 1), half = floor(total / 2),
             * we can safely say that we have found the median between these 4 variables.
             * If total is odd, since half = floor(total / 2), median = min(right_A, right_B).
             * Otherwise, median = (max(left_A, left_B) + min(right_A, right_B)) / 2.
             */
            return (total & 0x01) ? (double)((right_A > right_B) ? right_B : right_A) : ((((left_A > left_B) ? left_A : left_B) + ((right_A > right_B) ? right_B : right_A)) / 2.0);
        }
        else{
            /* 2 conditions: (left_A > right_B) or (left_B > right_A) */
            if (left_A > right_B)
                /**
                 * right is too much, we lower right to get less elements from A
                 * to form the left part of the merged array.
                 * Since the median of A[left:right] is too much, 
                 * we cut A in half to get the left part of A
                 * just like in binary search.
                 */
                right = i - 1;
            /**
             * Otherwise, the median of A[left:right] isn't enough, 
             * we cut A in half to get the right part of A
             * just like in binary search.
             */
            else left = i + 1;
        }
    }
    return 0.0;
}

int main()
{
    int nums1[] = {1, 2}, nums2[] = {3, 4};
    printf("%f", findMedianSortedArrays(nums1, 2, nums2, 2));
    return 0;
}
