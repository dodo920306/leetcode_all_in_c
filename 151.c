#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXIMUM_LENGTH 10000

char *reverseWords(char *s)
{
    int i = 0;
    char **words = (char **)malloc(strlen(s) * sizeof(char *)), *word = strtok(s, " ");
    if (!words) return NULL;
    while (word) {
        if (!(words[i] = (char *)calloc(strlen(word) + 1, sizeof(char))))   return NULL;
        strncat(words[i++], word, MAXIMUM_LENGTH);
        word = strtok(NULL, " ");
    }
    i--;
    *s = '\0';
    while (i > 0) {
        strncat(s, words[i], MAXIMUM_LENGTH);
        strncat(s, " ", MAXIMUM_LENGTH);
        free(words[i--]);
    }
    strncat(s, *words, MAXIMUM_LENGTH);
    free(*words);
    free(words);
    return s;
}

int main()
{
    char s[] = "the sky is blue";
    printf("%s\n", reverseWords(s));
    return 0;
}
