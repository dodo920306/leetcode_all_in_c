#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "uthash/include/uthash.h"

struct stringMap {
    char *key;
    int times;
    UT_hash_handle hh;
};

bool isInStringMap(struct stringMap **, char *);
bool insertStringMap(struct stringMap **, char *);
void freeStringMap(struct stringMap **);
void insertStringMapAfterStrtok(struct stringMap **, char *, char *);
char **uncommonFromSentences(char *s1, char *s2, int *returnSize);

bool isInStringMap(struct stringMap **map, char *key)
{
    struct stringMap *s;
    HASH_FIND_STR(*map, key, s); 
    return !!s;
}

bool insertStringMap(struct stringMap **map, char *key)
{
    struct stringMap *s;
    HASH_FIND_STR(*map, key, s); 
    if (!s && (s = (struct stringMap *)malloc(sizeof(struct stringMap)))) {
        s->key = key;
        s->times = 0;
        HASH_ADD_KEYPTR(hh, *map, s->key, strlen(s->key), s);
        return true;
    }
    else if (s)
        s->times++;
    return false;
}

void freeStringMap(struct stringMap **map)
{
    struct stringMap *s, *tmp;
    HASH_ITER(hh, *map, s, tmp) {
        HASH_DEL(*map, s);
        free(s);
    }
    free(map);
}

void insertStringMapAfterStrtok(struct stringMap **map, char *str, char *del)
{
    for (char *s = strtok(str, del); s; s = strtok(NULL, del))
        insertStringMap(map, s);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **uncommonFromSentences(char *s1, char *s2, int *returnSize)
{
    struct stringMap **wordsInS1 = (struct stringMap **)calloc(1, sizeof(struct stringMap *)), **wordsInS2 = (struct stringMap **)calloc(1, sizeof(struct stringMap *)), *s, *tmp;
    char **res = (char **)malloc(strlen(s1) * sizeof(char *));
    *returnSize = 0;
    if (!(wordsInS1 && wordsInS2 && res))   return NULL;

    insertStringMapAfterStrtok(wordsInS1, s1, " ");
    insertStringMapAfterStrtok(wordsInS2, s2, " ");
    HASH_ITER(hh, *wordsInS1, s, tmp) {
        if (!isInStringMap(wordsInS2, s->key) && !(s->times))
            res[(*returnSize)++] = s->key;
    }
    HASH_ITER(hh, *wordsInS2, s, tmp) {
        if (!isInStringMap(wordsInS1, s->key) && !(s->times))
            res[(*returnSize)++] = s->key;
    }
    freeStringMap(wordsInS1);
    freeStringMap(wordsInS2);

    return res;
}

void printStrArray(char **arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%s, ", arr[i]);
    }
    if (arrSize >= 0)
        printf("%s]\n", arr[arrSize]);
    else
        printf("]\n");
}

int main()
{
    int returnSize = 0;
    char s1[] = "this apple is sweet", s2[] = "this apple is sour";
    char **res = uncommonFromSentences(s1, s2, &returnSize);
    printStrArray(res, returnSize);
    free(res);
    return 0;
}
