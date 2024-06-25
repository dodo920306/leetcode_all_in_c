#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mergeAlternately(char *word1, char *word2);

char *mergeAlternately(char *word1, char *word2)
{
    char *res = (char *)calloc(strlen(word1) + strlen(word2) + 1, sizeof(char));
    int i = 0, j = 0, k = 0;
    if (strlen(word1) < strlen(word2)) {
        for (; j < strlen(word1); i++)   res[i] = i % 2 ? word2[k++] : word1[j++];
        while (k < strlen(word2))   res[i++] = word2[k++];
    }
    else {
        for (; k < strlen(word2); i++)   res[i] = i % 2 ? word2[k++] : word1[j++];
        while (j < strlen(word1))   res[i++] = word1[j++];
    }
    return res;
}

int main()
{
    char word1[] = "ab", word2[] = "pqrs", *res = mergeAlternately(word1, word2);
    printf("%s\n", res);
    free(res);
    return 0;
}
