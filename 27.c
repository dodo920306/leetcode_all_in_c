#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int removeElement(int* nums, int numsSize, int val);
int cmp(const void *a, const void *b);

int main()
{
    int nums[4] = {3, 2, 2, 3}; // Input array
    int val = 3; // Value to remove
    int expectedNums[2] = {2, 2}; // The expected answer with correct length.
                                  // It is sorted with no values equaling val.

    int k = removeElement(nums, 4, val); // Calls the implementation

    assert(k == sizeof(expectedNums) / sizeof(expectedNums[0]));
    qsort(nums, k, sizeof(nums[0]), cmp);
    for (int i = 0; i < k; i++) {
        assert(nums[i] == expectedNums[i]);
    }
    printf("ok!");
}

int removeElement(int* nums, int numsSize, int val)
{
    int *tmp_ptr = nums, *run_ptr = nums, *end_ptr = nums + numsSize;
    while (run_ptr != end_ptr) {
        if (*run_ptr != val) {
            *(tmp_ptr++) = *run_ptr;
        }
        run_ptr++;
    }
    return tmp_ptr - nums;
}

int cmp(const void *a, const void *b) {
   return *(int*)a - *(int*)b;
}
