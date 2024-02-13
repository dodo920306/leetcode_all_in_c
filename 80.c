#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

int removeDuplicates(int* nums, int numsSize);

int main()
{
    int nums[9] = {0, 0, 1, 1, 1, 1, 2, 3, 3}; // Input array
    int numsSize = 9; // Value to remove
    int expectedNums[7] = {0, 0, 1, 1, 2, 3, 3}; // The expected answer with correct length.

    int k = removeDuplicates(nums, numsSize); // Calls the implementation

    assert(k == sizeof(expectedNums) / sizeof(expectedNums[0]));
    for (int i = 0; i < k; i++) {
        assert(nums[i] == expectedNums[i]);
    }
    printf("ok!");
}

int removeDuplicates(int* nums, int numsSize)
{
    int *tmp_ptr = nums, *run_ptr = nums + 1, *end_ptr = nums + numsSize;
    bool twice = false;
    while (run_ptr != end_ptr) {
        if (*run_ptr != *tmp_ptr) {
            ++tmp_ptr;
            *tmp_ptr = *run_ptr;
            twice = false;
        }
        else if (!twice) {
            ++tmp_ptr;
            *tmp_ptr = *run_ptr;
            twice = true;
        }
        run_ptr++;
    }
    ++tmp_ptr;
    return tmp_ptr - nums;
}
