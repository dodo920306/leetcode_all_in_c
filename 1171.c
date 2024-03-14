#include <stdio.h>

/* This number was obtained through experiments */
#define HASH_SIZE 48510

struct ListNode {
    int val;
    struct ListNode *next;
};

int hash_function(int key);
void insert(struct ListNode *hashtable[], int key, struct ListNode *value);
struct ListNode *removeZeroSumSublists(struct ListNode *head);

int hash_function(int key)
{
    /**
     * We want to distinguish key and -key.
     * The parity of the result of the module in C depends on
     * that of the dividend, so we can get a different result.
     */
    return (key % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
}

void insert(struct ListNode *hashtable[], int key, struct ListNode *value)
{
    /**
     * What if there is a collision?
     * If the collision happens when there are same input keys, that's totally fine
     * because we want to update the key with the latest value.
     * Otherwise, that's not fine, and this is prevented by
     * the hash table that is large enough.
     */
    hashtable[hash_function(key)] = value;
}

struct ListNode *removeZeroSumSublists(struct ListNode *head)
{
    int sum = 0;
    /* We need a dummy node whose value is 0 to remove subsequences whose prefix sum is exactly  0. */
    struct ListNode front = {.val = 0, .next = head}, *pre = &front, *current = pre, *map[HASH_SIZE];

    while (current) {
        sum += current->val;
        /**
         * We insert nodes into the table based on the sum of previous values.
         * If there are two different nodes having the same prefix sum,
         * replace the old one with the later one.
         */
        insert(map, sum, current);
        current = current->next;
    }

    sum = 0;
    /* Nobody's next will be pre, so it's safe to set the beginning as pre. */
    current = pre;

    while (current) {
        sum += current->val;
        /**
         * For each sum, if there multiple of them in the table,
         * the table will only record the latest of them,
         * and the result list will cross all of them.
         * This is because if there are two nodes having the same prefix sum,
         * **the sum of nodes between them will be 0**.
         */
        current->next = map[hash_function(sum)]->next;
        current = current->next;
    }
    /* It's not safe to return head since the head itself may also get deleted. */
    return pre->next;
}

int main()
{
    struct ListNode node5 = {.val = 1, .next = NULL}, node4 = {.val = 3, .next = &node5}, node3 = {.val = -3, .next = &node4}, node2 = {.val = 2, .next = &node3}, node1 = {.val = 1, .next = &node2}, *res = removeZeroSumSublists(&node1);
    while (res) {
        printf("%d ", res->val);
        res = res->next;
    }
    return 0;
}
