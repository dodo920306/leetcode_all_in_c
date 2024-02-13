#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

bool hasCycle(struct ListNode *head);

bool hasCycle(struct ListNode *head)
{
    if (!head || !(head->next)) return false;
    struct ListNode *slow = head->next, *fast = head->next->next;
    while (fast) {
        if (fast == slow)   return true;
        slow = slow->next;
        fast = fast->next ? fast->next->next : NULL;
    }
    return false;
}

int main()
{
    struct ListNode node4 = {.val = -4, .next = NULL}, node3 = {.val = 0, .next = &node4}, node2 = {.val = 2, .next = &node3}, head = {.val = 3, .next = &node2};
    node4.next = &node2;

    printf("%s", hasCycle(&head) ? "true" : "false");
    return 0;
}
