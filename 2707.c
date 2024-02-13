#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int minExtraChar(char * s, char ** dictionary, int dictionarySize);

int main() {
    char s[10] = "leetscode";
    char* dictionary[3];
    dictionary[0] = malloc(5 * sizeof(char));
    dictionary[1] = malloc(5 * sizeof(char));
    dictionary[2] = malloc(9 * sizeof(char));
    *(dictionary) = "leet";
    *(dictionary + 1) = "code";
    *(dictionary + 2) = "leetcode";
    int dictionarySize = 3;
    printf("%d\n", minExtraChar(s, dictionary, dictionarySize));
}

int minExtraChar(char * s, char ** dictionary, int dictionarySize)
{
    int length = strlen(s) + 1;
    int* dp = (int *)malloc(length * sizeof(int));
    for (int i = 0; i < length; i++) {
        dp[i] = i;
    }
    for (int i = 1; i < length; i++)
    {
        dp[i] = MIN(dp[i], dp[i - 1] + 1);
        for (int j = 0; j < dictionarySize; j++)
        {
            if (strlen(dictionary[j]) <= i) {
                int k = strlen(dictionary[j]) - 1, h = i - 1;
                while (dictionary[j][k--] == s[h--]) {
                    if (k == -1) {
                        dp[i] = MIN(dp[i], dp[h + 1]);
                        break;
                    }
                }
            }
        }
    }
    return dp[length - 1];
}
