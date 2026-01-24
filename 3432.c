#include <stdio.h>

int countPartitions(int* nums, int numsSize);

int main() {
    int nums[] = {10, 10, 3, 7, 6};
    printf("%d\n", countPartitions(nums, 5));
    return 0;
}

int countPartitions(int* nums, int numsSize) {
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += nums[i];
    }
    return sum % 2 ? 0 : numsSize - 1;
}
