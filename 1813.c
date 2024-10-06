#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char **strToWords(char *, int *);
bool areWordsSimilar(char **, int, char **, int);
bool areSentencesSimilar(char *, char *);

char **strToWords(char *s, int *returnSize)
{
    char **res = (char **)malloc((strlen(s) + 1) / 2 * sizeof(char *)), \
         *delim = " ";
    if (!res) {
        fprintf(stderr, "Error: Memory Allcation Failed.");
        return NULL;
    }

    *returnSize = 0;
    for (char *i = strtok(s, delim); i; i = strtok(NULL, delim)) {
        res[*returnSize] = i;
        (*returnSize)++;
    }
    return res;
}

bool areWordsSimilar(char **shortWords, int shortWordsSize, char **longWords, int longWordsSize)
{
    int prefix = 0, suffix = 0;
    shortWordsSize--;
    longWordsSize--;

    for (; prefix <= shortWordsSize; prefix++)
        if (strcmp(shortWords[prefix], longWords[prefix])) break;

    for (int i = shortWordsSize, j = longWordsSize; i >= 0; i--) {
        if (strcmp(shortWords[i], longWords[j]))   break;
        suffix++;
        j--;
    }

    return shortWordsSize < prefix + suffix;
}

bool areSentencesSimilar(char *sentence1, char *sentence2)
{
    int words1Size = 0, words2Size = 0;
    char **words1 = NULL, **words2 = NULL;
    bool res = false;
    if (!strcmp(sentence1, sentence2))  return true;

    words1 = strToWords(sentence1, &words1Size);
    words2 = strToWords(sentence2, &words2Size);
    if (!(words1 && words2)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return false;
    }

    res = words1Size < words2Size ? areWordsSimilar(words1, words1Size, words2, words2Size) : areWordsSimilar(words2, words2Size, words1, words1Size);

    free(words1);
    free(words2);
    return res;
}

int main()
{
    char sentence1[] = "", sentence2[] = "";
    printf("%s\n", areSentencesSimilar(sentence1, sentence2) ? "true" : "false");
    return 0;
}
