#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head);
void reorderList(struct ListNode *head);

struct ListNode *reverseList(struct ListNode *head)
{
    struct ListNode *prev = NULL, *next;
    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

void reorderList(struct ListNode *head)
{
    if (head->next) {
        struct ListNode *slow = head, *fast = head, *temp;
        while (fast && fast->next) {
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        /* odd nodes */
        if (fast) {
            temp = slow;
            slow = slow->next;
        }
        /* divide the list in half */
        temp->next = NULL;
        /* reverse the latter half */
        fast = reverseList(slow);
        /* use another pointer to iterate the list */
        slow = head;

        while (fast) {
            /* insert fast into slow */
            temp = slow->next;
            slow->next = fast;
            slow = temp;
            /* insert slow into fast */
            temp = fast->next;
            fast->next = slow;
            fast = temp;
        }
    }
}

int main()
{
    struct ListNode node5 = {5, NULL}, node4 = {4, &node5}, node3 = {3, &node4}, node2 = {2, &node3}, node1 = {1, &node2}, *res = &node1;
    reorderList(res);
    while (res) {
        printf("%d ", res->val);
        res = res->next;
    }
    printf("\n");
    return 0;
}
