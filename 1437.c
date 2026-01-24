#include <stdio.h>
#include <stdbool.h>

bool kLengthApart(int* nums, int numsSize, int k);

int main() {
    int nums[] = {1, 0, 0, 0, 1, 0, 0, 1};
    printf(kLengthApart(nums, 8, 2) ? "true" : "false");
    printf("\n");
    return 0;
}

bool kLengthApart(int* nums, int numsSize, int k) {
    int firstElementAfterFirstOne = numsSize;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i]) {
            firstElementAfterFirstOne = i + 1;
            break;
        }
    }
    for (int i = firstElementAfterFirstOne, counter = 0; i < numsSize; i++) {
        if (nums[i]) {
            if (counter < k) {
                return false;
            }
            counter = 0;
        }
        else {
            counter++;
        }
    }
    return true;
}
