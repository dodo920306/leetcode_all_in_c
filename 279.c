#include <stdio.h>
#include <stdlib.h>

#define MIN(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b; })

int numSquares(int n)
{
    /* There are n + 1 integers need to be recorded during dp. */
    int *dp = (int *)malloc((n + 1) * sizeof(int)), res = n;
    if (!dp) {
        perror("Error: ");
        return -1;
    }
    dp[0] = 0;
    dp[1] = 1;
    if (n > 1) dp[2] = 2;
    if (n > 2) dp[3] = 3;
    for (int i = 4; i < n; i++) {
        /**
         * Pretend that every integer needs the value of itself as the number of perfect square numbers that sum to n first.
         * This hypothesis comes from considering k = 1 + 1 + 1 + 1 + ... = 1 * k as a worst case.
         * It works for small integers, as 1 = 1, 2 = 1 + 1, 3 = 1 + 1 + 1.
         * Also, dp[0] = 0 is needed. For example, dp[4] = dp[0] + 1 in the following loop,
         * The least number of perfect square numbers that sum to 4 is 1 since 4 = 4 = 2 * 2.
         * Thus, dp[0] has to be 0 to require the correct answer.
         */
        dp[i] = i;
        for (int j = 1; j * j <= i; j++)
            /**
                * A better answer could be gotten by taking j * j in the sum
                * while considering what's the least number of perfect square numbers that sum to the rest of the sum,
                * which is i - j * j. 
                */
            dp[i] = MIN(dp[i], dp[i - j * j] + 1);
    }
    for (int i = 1; i * i <= n; i++)
        res = MIN(res, dp[n - i * i] + 1);
    free(dp);
    return res;
}

int main()
{
    printf("%d\n", numSquares(12));
    return 0;
}
