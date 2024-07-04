#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *reverse(struct ListNode *prev, struct ListNode *head);
struct ListNode *reverseList(struct ListNode *head);

struct ListNode *reverse(struct ListNode *prev, struct ListNode *head)
{
    if (!head)  return prev;
    struct ListNode *next = head->next;
    head->next = prev;
    return reverse(head, next);
}

struct ListNode *reverseList(struct ListNode *head)
{
    return reverse(NULL, head);
}

int main()
{
    struct ListNode node5 = {5, NULL}, node4 = {4, &node5}, node3 = {3, &node4}, node2 = {2, &node3}, node1 = {1, &node2}, *head = reverseList(&node1);
    printf("[%d", head->val);
    head = head->next;
    while (head) {
        printf(", %d", head->val);
        head = head->next;
    }
    printf("]\n");
    return 0;
}
