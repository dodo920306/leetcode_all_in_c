#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TrieNode {
    int count;
    struct TrieNode *children[26];
};

struct TrieRoot {
    struct TrieNode *root;
};

int initIntArray(int **arr, int size);
int initTrieNode(struct TrieNode **node);
int insert(struct TrieRoot *self, char *s);
int getScore(struct TrieRoot *self, char *s);
int initTrieRoot(struct TrieRoot **root);
void freeTrieNode(struct TrieNode *node);
void freeTrieRoot(struct TrieRoot *root);
int *sumPrefixScores(char **words, int wordsSize, int *returnSize);

void printIntArray(int *arr, int arrSize);

int initIntArray(int **arr, int size)
{
    *arr = (int *)calloc(size, sizeof(int));
    if (!(*arr))    return -1;
    return 0;
}

int initTrieNode(struct TrieNode **node)
{
    *node = (struct TrieNode *)calloc(1, sizeof(struct TrieNode));
    if (!(*node))   return -1;
    return 0;
}

int insert(struct TrieRoot *self, char *s)
{
    struct TrieNode *iter = self->root;

    for (int i = 0, length = strlen(s), index; i < length; i++) {
        index = s[i] - 'a';
        if (!(iter->children[index]) && (initTrieNode(&(iter->children[index]))))
            return -1;
        iter = iter->children[index];
        iter->count++;
    }
    return 0;
}

int getScore(struct TrieRoot *self, char *s)
{
    struct TrieNode *iter = self->root;
    int res = 0;

    for (int i = 0, length = strlen(s), index; i < length; i++) {
        index = s[i] - 'a';
        iter = iter->children[index];
        res += iter->count;
    }
    return res;
}

int initTrieRoot(struct TrieRoot **root)
{
    *root = (struct TrieRoot *)malloc(sizeof(struct TrieRoot));

    if (!(*root))    return -1;

    return initTrieNode(&((*root)->root));
}

void freeTrieNode(struct TrieNode *node)
{
    if (!node)  return;

    for (int i = 0; i < 26; i++) 
        freeTrieNode(node->children[i]);
    free(node);
}

void freeTrieRoot(struct TrieRoot *root)
{
    freeTrieNode(root->root);
    free(root);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sumPrefixScores(char **words, int wordsSize, int *returnSize)
{
    int *res = NULL;
    struct TrieRoot *trie = NULL;

    *returnSize = 0;
    if (initTrieRoot(&trie) || initIntArray(&res, wordsSize))
        return NULL;

    for (int i = 0; i < wordsSize; i++)
        insert(trie, words[i]);

    for (int i = 0; i < wordsSize; i++)
        res[(*returnSize)++] = getScore(trie, words[i]);
    
    freeTrieRoot(trie);
    return res;
}

void printIntArray(int *arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[arrSize]);
}

int main()
{
    char *words[] = {"abc", "ab", "bc", "b"};
    int returnSize = 0, *res = sumPrefixScores(words, 4, &returnSize);
    printIntArray(res, returnSize);
    free(res);
    return 0;
}
