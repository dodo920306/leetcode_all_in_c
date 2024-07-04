#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *mergeNodes(struct ListNode *head);

struct ListNode *mergeNodes(struct ListNode *head)
{
    struct ListNode *i = head, *j = head->next;
    while (j) {
        if (j->val) i->val += j->val;
        else {
            i = i->next;
            i->val = 0;
        }
        j = j->next;
    }
    j = head;
    while (j->next != i)    j = j->next;
    j->next = NULL;
    return head;
}

int main()
{
    struct ListNode node7 = {0, NULL}, node6 = {2, &node7}, node5 = {2, &node6}, node4 = {0, &node5}, node3 = {3, &node4}, node2 = {0, &node3}, node1 = {1, &node2}, head = {0, &node1}, *res = mergeNodes(&head);
    if (res) {
        printf("[%d", res->val);
        res = res->next;
        while (res) {
            printf(", %d", res->val);
            res = res->next;
        }
    }
    else
        printf("[");
    printf("]\n");
    return 0;
}
