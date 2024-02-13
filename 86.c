#include <stdio.h>
#include <stdlib.h>

/**
 * The solution comes from https://hackmd.io/@sysprog/c-linked-list.
 * Please consider referring to that before contributing this file.
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* partition(struct ListNode *head, int x);

struct ListNode* partition(struct ListNode *head, int x)
{
    struct ListNode **head1 = &head, *list2 = NULL, **head2 = &list2;
    for (struct ListNode *i = head, ***indir; i; i = i->next) {
        /**
         * decide which list i belongs to.
         * A pointer to the pointer to the pointer of the node is needed here to change the value genuinely.
         */
        indir = i->val < x ? &head1: &head2;
        /* append the node into the corresponding list i.e. change the current value to the node value. */
        **indir = i;
        /* move the list ahead */
        *indir = &((**indir)->next);
    }
    /* concat 2 lists */
    *head1 = list2;
    *head2 = NULL;
    return head;
}

int main()
{
    struct ListNode node6 = {.val = 2, .next = NULL}, node5 = {.val = 5, .next = &node6}, node4 = {.val = 2, .next = &node5}, node3 = {.val = 3, .next = &node4}, node2 = {.val = 4, .next = &node3}, head = {.val = 1, .next = &node2}, *res;

    res = partition(&head, 3);
    while (res)
    {
        printf("%d ", res->val);
        res = res->next;
    }
    return 0;
}
