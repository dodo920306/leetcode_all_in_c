#include <stdio.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *reverseList(struct ListNode *head);
bool isPalindrome(struct ListNode *head);

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

bool isPalindrome(struct ListNode *head)
{
    if (head->next) {
        struct ListNode *slow = head, *fast = head, *temp;
        while (fast && fast->next) {
            temp = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        /* odd nodes */
        if (fast)
            slow = slow->next;
        temp->next = NULL;
        temp = reverseList(slow);

        while (head) {
            if (head->val != temp->val) return false;
            head = head->next;
            temp = temp->next;
        }
    }
    return true;
}

int main()
{
    struct ListNode node4 = {1, NULL}, node3 = {2, &node4}, node2 = {2, &node3}, node1 = {1, &node2};
    printf("%s\n", isPalindrome(&node1) ? "true" : "false");
    return 0;
}
