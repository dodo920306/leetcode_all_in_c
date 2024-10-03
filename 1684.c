#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int lowercaseCharConverter(char);
int countConsistentStrings(char *, char **, int);

int lowercaseCharConverter(char c)
{
    return c - 'a';
}

int countConsistentStrings(char *allowed, char **words, int wordsSize)
{
    int res = 0;
    bool isAllowed[26] = { false };
    for (int i = 0, length = strlen(allowed); i < length; i++)
        isAllowed[lowercaseCharConverter(allowed[i])] = true;
    for (int i = 0, j, length; i < wordsSize; i++) {
        j = 0;
        length = strlen(words[i]);
        while (j < length && isAllowed[lowercaseCharConverter(words[i][j])])
            j++;
        res += (j == length);
    }
    return res;
}

int main()
{
    char *words[] = {"ad", "bd", "aaab", "baa", "badab"};
    printf("%d\n", countConsistentStrings("ab", words, 5));
    return 0;
}
