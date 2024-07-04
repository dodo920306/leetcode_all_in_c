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

struct ListNode* deleteMiddle(struct ListNode *head);

struct ListNode* deleteMiddle(struct ListNode *head)
{
    struct ListNode **indir = &head;
    for (struct ListNode *fast = head; fast && fast->next; fast = fast->next->next)
        indir = &((*indir)->next);
    /**
     * If the space of the deleted node is malloced, and it needs to be freed,
     * then a struct ListNode * valuable needs to be declared here to save the original *indir (the deleted node).
     * e.g. struct ListNode *del = *indir;
     * Then, free it right before the return.
     * Here, the nodes aren't malloced. Thus no free is needed.
     */
    *indir = (*indir)->next; /* update the deleted node now as the next node */
    return head;
}

int main()
{
    struct ListNode node7 = {.val = 6, .next = NULL}, node6 = {.val = 2, .next = &node7}, node5 = {.val = 1, .next = &node6}, node4 = {.val = 7, .next = &node5}, node3 = {.val = 4, .next = &node4}, node2 = {.val = 3, .next = &node3}, head = {.val = 1, .next = &node2}, *res;

    res = deleteMiddle(&head);
    printf("[%d", res->val);
    res = res->next;
    while (res) {
        printf(", %d", res->val);
        res = res->next;
    }
    printf("]\n");
    return 0;
}
