#include <stdio.h>
#include <stdlib.h>

int maxSumAfterPartitioning(int *arr, int arrSize, int k);

int maxSumAfterPartitioning(int *arr, int arrSize, int k)
{
    int *dp = (int *)malloc((arrSize + 1) * sizeof(int));
    if (!dp) {
        perror("Error");
        return -1;
    }
    /**
     * We need an empty element as the end of dp as the condition "Nothing is considered in this partition".
     * That why the array is one element more than the origin.
     */
    for (int i = 0, max; i <= arrSize; i++) {
        /* calculate maxSumAfterPartitioning for array ending at arr[i - 1]. */
        dp[i] = 0;
        for (int j = 1, local_sum, max = INT_MIN; j <= k && j <= i; j++) {
            /**
             * j is the length of partition that's the current consideration.
             * if j == i, a whole partition from the head to i - 1 is considered.
             * We update the local maximum while considering each of the element one by one.
             * Then, we update the local partition sum with the local maximum.
             */
            if (arr[i - j] > max)   max = arr[i - j];
            local_sum = dp[i - j] + max * j;
            if (local_sum > dp[i])  dp[i] = local_sum;
        }
    }
    return dp[arrSize];
}

int main()
{
    int arr[] = {1,15,7,9,2,5,10};
    printf("%d", maxSumAfterPartitioning(arr, 7, 3));
    return 0;
}
