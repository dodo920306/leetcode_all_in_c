#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2)
{
    int carry = 0;
    struct ListNode *sum = (struct ListNode *)malloc(sizeof(struct ListNode)), *head = sum;
    sum->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    while (l1 && l2) {
        sum = sum->next;
        sum->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        sum->val = l1->val + l2->val + carry;
        carry = sum->val / 10;
        sum->val %= 10;
        l1 = l1->next;
        l2 = l2->next;
    }
    while (l1) {
        sum = sum->next;
        sum->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        sum->val = l1->val + carry;
        carry = sum->val / 10;
        sum->val %= 10;
        l1 = l1->next;
    }
    while (l2) {
        sum = sum->next;
        sum->next = (struct ListNode *)malloc(sizeof(struct ListNode));
        sum->val = l2->val + carry;
        carry = sum->val / 10;
        sum->val %= 10;
        l2 = l2->next;
    }
    if (carry) {
        sum = sum->next;
        sum->val = carry;
    }
    else
        free(sum->next);
    sum->next = NULL;
    sum = head->next;
    free(head);
    return sum;
}

int main()
{
    return 0;
}
