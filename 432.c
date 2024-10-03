#include <stdio.h>
#include <stdlib.h>
#include "uthash/include/uthash.h"

struct setStr {
    char key[11];
    UT_hash_handle hh;
};

struct dequeNode {
    int freq;
    struct setStr *set;
    struct dequeNode *next, *prev;
};

struct mapStrDequeNode {
    char key[11];
    struct dequeNode *val;
    UT_hash_handle hh;
};

typedef struct {
    struct mapStrDequeNode *map;
    struct dequeNode *root;
} AllOne;

AllOne *allOneCreate();
void allOneInc(AllOne *, char *);
void allOneDec(AllOne *, char *);
char *allOneGetMaxKey(AllOne *);
char *allOneGetMinKey(AllOne *);
void allOneFree(AllOne *obj);

AllOne *allOneCreate()
{
    AllOne *res = (AllOne *)malloc(sizeof(AllOne));
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    res->root = (struct dequeNode *)malloc(sizeof(struct dequeNode));
    if (!(res->root)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    res->map = NULL;
    res->root->prev = res->root;
    res->root->next = res->root;
    return res;
}

void allOneInc(AllOne *obj, char *key)
{
    struct mapStrDequeNode *keyMap = NULL;
    struct dequeNode *prevNode = NULL, *keyNode = NULL, *nextNode = NULL, *newNode = NULL;
    struct setStr *keySet = NULL;
    int freq = 0;

    HASH_FIND_STR(obj->map, key, keyMap);
    if (keyMap) {
        keyNode = keyMap->val;
        freq = keyNode->freq;
        HASH_FIND_STR(keyNode->set, key, keySet);
        HASH_DEL(keyNode->set, keySet);
        nextNode = keyNode->next;
        if (nextNode == obj->root || nextNode->freq != freq + 1) {
            newNode = (struct dequeNode *)malloc(sizeof(struct dequeNode));
            if (!newNode) {
                fprintf(stderr, "Error: Memory Allocation Failed.");
                return;
            }

            newNode->freq = freq + 1;
            newNode->set = NULL;
            HASH_ADD_STR(newNode->set, key, keySet);
            newNode->prev = keyNode;
            newNode->next = nextNode;
            keyNode->next = newNode;
            nextNode->prev = newNode;
            keyMap->val = newNode;
        }
        else {
            HASH_ADD_STR(nextNode->set, key, keySet);
            keyMap->val = nextNode;
        }

        if (!(HASH_COUNT(keyNode->set))) {
            prevNode = keyNode->prev;
            nextNode = keyNode->next;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
            free(keyNode);
        }
    }
    else {
        nextNode = obj->root->next;
        keyMap = (struct mapStrDequeNode *)malloc(sizeof(struct mapStrDequeNode));
        keySet = (struct setStr *)malloc(sizeof(struct setStr));

        if (!keyMap || !keySet) {
            fprintf(stderr, "Error: Memory Allocation Failed.");
            return;
        }
        strncpy(keyMap->key, key, 10);
        (keyMap->key)[10] = '\0';
        HASH_ADD_STR(obj->map, key, keyMap);
        strncpy(keySet->key, key, 10);
        (keySet->key)[10] = '\0';

        if (nextNode == obj->root || nextNode->freq > 1) {
            keyNode = obj->root;
            newNode = (struct dequeNode *)malloc(sizeof(struct dequeNode));
            if (!newNode) {
                fprintf(stderr, "Error: Memory Allocation Failed.");
                return;
            }

            newNode->freq = 1;
            newNode->set = NULL;
            HASH_ADD_STR(newNode->set, key, keySet);
            newNode->prev = keyNode;
            newNode->next = nextNode;
            keyNode->next = newNode;
            nextNode->prev = newNode;
            keyMap->val = newNode;
        }
        else {
            HASH_ADD_STR(nextNode->set, key, keySet);
            keyMap->val = nextNode;
        }
    }
}

void allOneDec(AllOne *obj, char *key)
{
    struct mapStrDequeNode *keyMap = NULL;
    struct dequeNode *prevNode = NULL, *keyNode = NULL, *nextNode = NULL, *newNode = NULL;
    struct setStr *keySet = NULL;
    int freq = 0;

    HASH_FIND_STR(obj->map, key, keyMap);
    if (!keyMap) return;

    keyNode = keyMap->val;
    HASH_FIND_STR(keyNode->set, key, keySet);
    HASH_DEL(keyNode->set, keySet);
    freq = keyNode->freq;

    if (freq == 1) {
        HASH_DEL(obj->map, keyMap);
    }
    else {
        prevNode = keyNode->prev;
        if (prevNode == obj->root || prevNode->freq != freq - 1) {
            newNode = (struct dequeNode *)malloc(sizeof(struct dequeNode));
            if (!newNode) {
                fprintf(stderr, "Error: Memory Allocation Failed.");
                return;
            }

            newNode->freq = freq - 1;
            newNode->set = NULL;
            HASH_ADD_STR(newNode->set, key, keySet);
            newNode->prev = prevNode;
            newNode->next = keyNode;
            prevNode->next = newNode;
            keyNode->prev = newNode;
            keyMap->val = newNode;
        }
        else {
            HASH_ADD_STR(prevNode->set, key, keySet);
            keyMap->val = prevNode;
        }
    }

    if (!(HASH_COUNT(keyNode->set))) {
        prevNode = keyNode->prev;
        nextNode = keyNode->next;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        free(keyNode);
    }
}

char *allOneGetMaxKey(AllOne *obj)
{
    return obj->root->prev != obj->root ? obj->root->prev->set->key : "";
}

char *allOneGetMinKey(AllOne *obj)
{
    return obj->root->next != obj->root ? obj->root->next->set->key : "";
}

void allOneFree(AllOne *obj)
{
    for (struct dequeNode *i = obj->root->next, *nextNode; i != obj->root; i = nextNode) {
        for (struct setStr *j = i->set, *nextSet; j; j = nextSet) {
            nextSet = j->hh.next;
            free(j);
        }
        nextNode = i->next;
        free(i);
    }

    for (struct mapStrDequeNode *i = obj->map, *nextMap; i; i = nextMap) {
        nextMap = i->hh.next;
        free(i);
    }

    free(obj->root);
    free(obj);
}

/**
 * Your AllOne struct will be instantiated and called as such:
 * AllOne* obj = allOneCreate();
 * allOneInc(obj, key);
 
 * allOneDec(obj, key);
 
 * char* param_3 = allOneGetMaxKey(obj);
 
 * char* param_4 = allOneGetMinKey(obj);
 
 * allOneFree(obj);
*/

int main()
{
    AllOne *allOne = allOneCreate();
    if (!allOne)    return -1;
    printf("[null");
    allOneInc(allOne, "hello");
    printf(", null");
    allOneInc(allOne, "hello");
    printf(", null");
    printf(", %s", allOneGetMaxKey(allOne)); // return "hello"
    printf(", %s", allOneGetMinKey(allOne)); // return "hello"
    allOneInc(allOne, "leet");
    printf(", null");
    printf(", %s", allOneGetMaxKey(allOne)); // return "hello"
    printf(", %s", allOneGetMinKey(allOne)); // return "leet"
    allOneFree(allOne);
    printf("]\n");
    return 0;
}
