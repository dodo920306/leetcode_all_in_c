#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MODULO 1000000007
#define BASE 26

bool isNotAString(char *);
char *reverseString(char *);
int charToBase26Plus1(char);
char *shortestPalindrome(char *);

bool isNotAString(char *s)
{
    return (!s || !(*s) || !(s[1]));
}

char *reverseString(char *s)
{
    int length = strlen(s);
    char *_s = (char *)calloc(length + 1, sizeof(char)), tmp;

    strcpy(_s, s);

    for (int i = 0, j = length - 1; i < j; i++) {
        tmp = _s[i];
        _s[i] = _s[j];
        _s[j] = tmp;
        j--;
    }
    return _s;
}

int charToBase26Plus1(char c)
{
    return c - '`';
}

char *shortestPalindrome(char *s)
{
    long long prefix = 0, suffix = 0, length = strlen(s), power = 1;
    int endOfLongestPalindromeStartingFromTheBeginning = 0;
    char *res = NULL, *reverseSuffix = NULL;

    if (isNotAString(s))
        return s;

    for (int i = 0, digit; i < length; i++) {
        digit = charToBase26Plus1(s[i]);

        prefix = prefix * BASE % MODULO;
        prefix = (prefix + digit) % MODULO;

        suffix = (suffix + charToBase26Plus1(s[i]) * power) % MODULO;

        if (prefix == suffix)
            endOfLongestPalindromeStartingFromTheBeginning = i;

        power = power * BASE % MODULO;
    }

    res = (char *)calloc((2 * length - endOfLongestPalindromeStartingFromTheBeginning + 1), sizeof(char));

    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed");
        return NULL;
    }

    endOfLongestPalindromeStartingFromTheBeginning++;
    reverseSuffix = reverseString(s + endOfLongestPalindromeStartingFromTheBeginning);

    strcpy(res, reverseSuffix);
    strcpy(res + length - endOfLongestPalindromeStartingFromTheBeginning, s);

    free(reverseSuffix);
    return res;
}

int main()
{
    printf("%s\n", shortestPalindrome("aacecaaa"));
    return 0;
}
