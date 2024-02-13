#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool isPalindrome(char *s, int length);
char *firstPalindrome(char **words, int wordsSize);

bool isPalindrome(char *s, int length)
{
    for (int i = 0, j = length - 1; i < j; i++, j--)
        if (s[i] != s[j]) return false;
    return true;
}

char *firstPalindrome(char **words, int wordsSize)
{
    for (int i = 0; i < wordsSize; i++, words++)
        if (isPalindrome(*words, strlen(*words)))   return *words;
    return "";
}

int main()
{
    int wordsSize = 5;
    char **words = (char **)malloc(wordsSize * sizeof(char *));
    if (!words) return 1;
    for (int i = 0; i < wordsSize; i++) {
        words[i] = (char *)malloc(8 * sizeof(char));
        if (!words[i]) return i + 2;
    }
    words[0] = "abc";
    words[1] = "car";
    words[2] = "ada";
    words[3] = "racecar";
    words[4] = "cool";
    printf("%s", firstPalindrome(words, wordsSize));
    for (int i = 0; i < wordsSize; i++)
        free(words[i]);
    free(words);
    return 0;
}
