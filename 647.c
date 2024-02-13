#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int countSubstrings(char* s);

/**
 * A slower, but cooler solution with dp.
 * 
 * The redundant time are spent on malloc and free,
 * and the loop is unbreakable in the middle,
 * or the values of the matrix may not be true.
 * 
 * Moreover, the implementation in the following didn't check
 * if malloc() is successful, but it has already been slower.
 * 
 * int countSubstrings(char* s)
 * {
 *     int length = strlen(s), res = 0;
 *     bool **dp = (bool **)malloc(length * sizeof(bool *));
 *     for (int i = length - 1; i >= 0; i--) {
 *         dp[i] = (bool *)malloc(length * sizeof(bool));
 *         for (int j = i; j < length; j++) {
 * 
 *             don't break this.
 * 
 *             dp[i][j] is true if s[i ~ j] is a palindrome.
 *             This includes that (s[i] == s[j]) and dp[i + 1][j - 1].
 * 
 *             When ((j - i) < 3), dp[i + 1][j - 1] must be true, and
 *             if the judgement only relies on dp[i + 1][j - 1],
 *             i + 1 > j - 1 could happen and break the process.
 * 
 *             dp[i][j] = (s[i] == s[j]) && (((j - i) < 3) || dp[i + 1][j - 1]);
 *             res += (int)dp[i][j];
 *         }
 *     }
 *     for (int i = 0; i < length; i++)
 *         free(dp[i]);
 *     free(dp);
 *     return res;
 * }
 */

int countSubstrings(char* s)
{
    int length = strlen(s), res = 0;
    for (int i = 0; i < length; i++) {
        /* check if i is in the middle of a palindrome with a odd length */
        for (int j = i, k = i; j >= 0 && k < length;) {
            if (s[j--] == s[k++])   res++;
            else break;
        }
        /* check if i is in the middle of a palindrome with a even length */
        for (int j = i, k = i + 1; j >= 0 && k < length;) {
            if (s[j--] == s[k++])   res++;
            else break;
        }
    }
    return res;
}

int main()
{
    printf("%d", countSubstrings("abc"));
    return 0;
}
