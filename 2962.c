#include <stdio.h>

long long countSubarrays(int *nums, int numsSize, int k);

long long countSubarrays(int *nums, int numsSize, int k)
{
    int max = nums[0];
    long long res = 0;
    for (int i = 1; i < numsSize; i++)  if (max < nums[i])  max = nums[i];

    for (int i = 0, counter = 0, j = 0; j < numsSize; j++)
        if (nums[j] == max) {
            counter++;
            while (counter == k) {
                res += numsSize - j;
                counter -= (nums[i++] == max);
            }
        }

    return res;
}

int main()
{
    int nums[] = {1, 3, 2, 3, 3};
    printf("%lld\n", countSubarrays(nums, 5, 2));
    return 0;
}
