#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minExtraChar(char *, char **, int);

int minExtraChar(char *s, char **dictionary, int dictionarySize)
{
    int length = strlen(s);
    int* dp = (int *)malloc((length + 1) * sizeof(int)), res = 0;
    dp[0] = 0;
    for (int i = 1; i <= length; i++) {
        dp[i] = dp[i - 1] + 1;
        for (int j = 0, k; j < dictionarySize; j++) {
            k = strlen(dictionary[j]);
            if (k > i)  continue;
            k--;
            for (int h = i - 1; dictionary[j][k] == s[h]; h--) {
                if (!k) {
                    if (dp[h] < dp[i])
                        dp[i] = dp[h];
                    break;
                }
                k--;
            }
        }
    }
    res = dp[length];
    free(dp);
    return res;
}

int main() {
    char *dictionary[] = {"leet", "code", "leetcode"};
    printf("%d\n", minExtraChar("leetscode", dictionary, 3));
    return 0;
}
