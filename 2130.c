#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *reverse(struct ListNode *prev, struct ListNode *head);
int pairSum(struct ListNode *head);

struct ListNode *reverse(struct ListNode *prev, struct ListNode *head)
{
    if (!head)  return prev;
    struct ListNode *next = head->next;
    head->next = prev;
    return reverse(head, next);
}

int pairSum(struct ListNode *head)
{
    int res = 0;
    struct ListNode *fast = head, *slow = head, *i = head, *j;
    while (fast) {
        fast = fast->next->next;
        slow = slow->next;
    }
    j = reverse(NULL, slow);
    while (j) {
        i->val += j->val;
        if (res < i->val)
            res = i->val;
        i = i->next;
        j = j->next;
    }
    return res;
}

int main()
{
    struct ListNode node3 = {3, NULL}, node2 = {2, &node3}, node1 = {2, &node2}, head = {4, &node1};
    printf("%d\n", pairSum(&head));
    return 0;
}
