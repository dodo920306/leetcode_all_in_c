#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_KEY 10000
#define NUMBER_OF_BITS_FOR_AN_INT_MINUS_1 31

struct Node {
    int key, val;
    /**
     * Double pointers are used here to reduce put/get operation time to O(1)
     * since prev can be used to find the former node of the deleted node
     * and the end of the cache.
     */
    struct Node *prev, *next;
};

typedef struct {
    struct Node *head;
    int capacity;
    /**
     * The map is used to here to 
     * allow put/get operations get the target by its key as fast as possible.
     * The index is the key, while the value be the pointer of the node.
     */
    struct Node **map;
} LRUCache;

struct Node *new_node();
LRUCache *lRUCacheCreate(int capacity);
int lRUCacheGet(LRUCache *obj, int key);
void lRUCachePut(LRUCache *obj, int key, int value);
void lRUCacheFree(LRUCache *obj);

struct Node *new_node()
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (!node) {
        perror("Error");
        return NULL;
    }
    node->key = node->val = -1;
    node->prev = node->next = node;
    return node;
}

LRUCache *lRUCacheCreate(int capacity)
{
    struct Node *iter = NULL;
    LRUCache *obj = (LRUCache *)malloc(capacity * sizeof(LRUCache));
    if (!obj) {
        perror("Error");
        return NULL;
    }
    obj->map = (struct Node **)calloc(MAX_KEY, sizeof(struct Node *));
    if (!(obj->map)) {
        perror("Error");
        return NULL;
    }
    obj->head = new_node();
    obj->capacity = capacity;
    iter = obj->head;
    for (int i = 1; i < capacity; i++) {
        iter->next = new_node();
        iter->next->prev = iter;
        iter = iter->next;
    }
    iter->next = obj->head;
    obj->head->prev = iter;
    return obj;
}

int lRUCacheGet(LRUCache *obj, int key)
{
    struct Node *iter = obj->map[key];
    if (iter) {
        /* If the target is at the head, just move ahead the head pointer. */
        if (iter == obj->head)  obj->head = obj->head->next;
        else {
            /* If not, move the target to the end. */
            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;
            obj->head->prev->next = iter;
            iter->prev = obj->head->prev;
            iter->next = obj->head;
            obj->head->prev = iter;
        }
        return iter->val;
    }
    return -1;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
    struct Node *iter = obj->map[key];
    if (iter) {
        iter->val = value;
        /* similar to get */
        if (iter == obj->head)  obj->head = obj->head->next;
        else {
            iter->prev->next = iter->next;
            iter->next->prev = iter->prev;
            obj->head->prev->next = iter;
            iter->prev = obj->head->prev;
            iter->next = obj->head;
            obj->head->prev = iter;
        }
    }
    else {
        /* If the head isn't negative (empty), it's NULL (popped). */
        if (!(obj->head->key >> NUMBER_OF_BITS_FOR_AN_INT_MINUS_1))
            obj->map[obj->head->key] = NULL;

        /* insert at the original head */
        iter = obj->head;
        /* move head ahead */
        obj->head = obj->head->next;
        /* insert at the new end */
        iter->key = key;
        iter->val = value;

        obj->map[key] = iter;
    }
}

void lRUCacheFree(LRUCache *obj)
{
    struct Node *iter;
    for (int i = 0; i < obj->capacity; i++) {
        iter = obj->head;
        obj->head = obj->head->next;
        free(iter);
    }
    free(obj->map);
    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/
int main()
{
    LRUCache *lRUCache = lRUCacheCreate(2);
    lRUCachePut(lRUCache, 1, 1); // cache is {1=1}
    lRUCachePut(lRUCache, 2, 2); // cache is {1=1, 2=2}
    printf("%d\n", lRUCacheGet(lRUCache, 1));    // return 1 (not found)
    lRUCachePut(lRUCache, 3, 3); // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
    printf("%d\n", lRUCacheGet(lRUCache, 2));    // return -1 (not found)
    lRUCachePut(lRUCache, 4, 4); // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
    printf("%d\n", lRUCacheGet(lRUCache, 1));    // return -1 (not found)
    printf("%d\n", lRUCacheGet(lRUCache, 3));    // return 3
    printf("%d\n", lRUCacheGet(lRUCache, 4));    // return 4
    return 0;
}
