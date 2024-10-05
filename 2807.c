#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode {
    int val;
    struct ListNode *next;
};

int getGreatestCommonDivisors(int a, int b);
bool insertListNode(struct ListNode *prev, int targetVal, struct ListNode *next);
struct ListNode *insertGreatestCommonDivisors(struct ListNode *head);

int getGreatestCommonDivisors(int a, int b)
{
    return a ? getGreatestCommonDivisors(b % a, a) : b;
}

bool insertListNode(struct ListNode *prev, int targetVal, struct ListNode *next)
{
    struct ListNode *target = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!target)    return false;

    prev->next = target;
    target->next = next;
    target->val = targetVal;
    return true;
}

struct ListNode *insertGreatestCommonDivisors(struct ListNode *head)
{
    struct ListNode *iter = head;
    while (iter && iter->next)
        if (insertListNode(iter, getGreatestCommonDivisors(iter->val, iter->next->val), iter->next))
            iter = iter->next->next;
        else
            return NULL;
    return head;
}

int main()
{
    struct ListNode *node4 = (struct ListNode *)malloc(sizeof(struct ListNode)), \
                    *node3 = (struct ListNode *)malloc(sizeof(struct ListNode)), \
                    *node2 = (struct ListNode *)malloc(sizeof(struct ListNode)), \
                    *node1 = (struct ListNode *)malloc(sizeof(struct ListNode)), \
                    *res = NULL, *tmp;
    if (!(node1 && node2 && node3 && node4)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return -1;
    }

    node1->val = 18;
    node1->next = node2;

    node2->val = 6;
    node2->next = node3;

    node3->val = 10;
    node3->next = node4;

    node4->val = 3;
    node4->next = NULL;

    res = insertGreatestCommonDivisors(node1);
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return -1;
    }

    printf("%d", res->val);
    tmp = res->next;
    free(res);
    res = tmp;
    while (res) {
        printf(" -> %d", res->val);
        tmp = res->next;
        free(res);
        res = tmp;
    }
    printf("\n");
    return 0;
}
