#include <stdio.h>
#include <stdlib.h>

int specialTriplets(int* nums, int numsSize);

int main() {
    int nums[] = {6, 3, 6};
    printf("%d\n", specialTriplets(nums, 3));
    return 0;
}

int specialTriplets(int* nums, int numsSize) {
    int max = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    int *frequencies = calloc(max + 2, sizeof(int));
    int *previousFrequencies = calloc(max + 2, sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        frequencies[nums[i]]++;
    }

    long res = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max / 2) {
            previousFrequencies[nums[i]]++;
            continue;
        }

        int previousFrequency = previousFrequencies[2 * nums[i]];
        previousFrequencies[nums[i]]++;
        res = (res + (long) previousFrequency * (frequencies[2 * nums[i]] - previousFrequencies[2 * nums[i]])) % 1000000007;
    }
    free(frequencies);
    free(previousFrequencies);
    return (int) res;
}
