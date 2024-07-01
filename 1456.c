#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isAVowel(char c)
{
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int maxVowels(char *s, int k)
{
    int res, sum = 0, sSize = strlen(s);
    for (int i = 0; i < sSize; i++) s[i] = isAVowel(s[i]);
    for (int i = 0; i < k; i++) sum += s[i];
    res = sum;
    for (int i = 0; i + k < sSize; i++) {
        sum += s[i + k] - s[i];
        if (res < sum)  res = sum;
    }
    return res;
}

int main()
{
    char s[] = "leetcode";
    printf("%d\n", maxVowels(s, 3));
    return 0;
}
