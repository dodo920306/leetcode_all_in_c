#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *middleNode(struct ListNode *head);

struct ListNode *middleNode(struct ListNode *head)
{
    struct ListNode *fast = head;
    while (fast && fast->next) {
        fast = fast->next->next;
        head = head->next;
    }
    return head;
}

int main()
{
    struct ListNode node6 = {.val = 6, .next = NULL}, node5 = {.val = 5, .next = &node6}, node4 = {.val = 4, .next = &node5}, node3 = {.val = 3, .next = &node4}, node2 = {.val = 2, .next = &node3}, node1 = {.val = 1, .next = &node2}, *res = middleNode(&node1);
    while (res) {
        printf("%d ", res->val);
        res = res->next;
    }
    return 0;
}
