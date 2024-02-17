#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2);

/* a no malloc() solution */
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2)
{
    int carry = 0;
    struct ListNode *head = l1;
    while (l1->next && l2->next) {
        l1->val += l2->val + carry;
        carry = l1->val / 10;
        l1->val %= 10;
        l1 = l1->next;
        l2 = l2->next;
    }

    l1->val += l2->val + carry;
    carry = l1->val / 10;
    l1->val %= 10;

    /* use the original list space to store the result */ 
    if (l2->next)   l1->next = l2->next;

    if (l1->next) {
        l1 = l1->next;

        while (l1->next) {
            l1->val += carry;
            carry = l1->val / 10;
            l1->val %= 10;
            l1 = l1->next;
        }

        l1->val += carry;
        carry = l1->val / 10;
        l1->val %= 10;
    }

    /* l2 must haven't been used */ 
    if (carry) {
        l1->next = l2;
        l1 = l1->next;
        l1->val = carry;
    }

    l1->next = NULL;
    return head;
}

int main()
{
    struct ListNode *l1 = (struct ListNode *)malloc(sizeof(struct ListNode)), *l2 = (struct ListNode *)malloc(sizeof(struct ListNode)), *res, *iter;
    if (!l1 || !l2) {
        perror("Error");
        return -1;
    }
    l1->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!(l1->next)) {
        perror("Error");
        return -1;
    }
    l1->val = 2;
    l1->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!(l1->next->next)) {
        perror("Error");
        return -1;
    }
    l1->next->val = 4;
    l1->next->next->next = NULL;
    l1->next->next->val = 3;
    l2->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!(l2->next)) {
        perror("Error");
        return -1;
    }
    l2->val = 5;
    l2->next->next = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (!(l2->next->next)) {
        perror("Error");
        return -1;
    }
    l2->next->val = 6;
    l2->next->next->next = NULL;
    l2->next->next->val = 4;
    res = addTwoNumbers(l1, l2);
    while (res) {
        printf("%d ", res->val);
        res = res->next;
    }
    /**
     * No matter what we do to l1 and l2 in the function, 
     * the values they have here won't change, so we can free them.
     */
    while (l1) {
        iter = l1->next;
        free(l1);
        l1 = iter;
    }
    while (l2) {
        iter = l2->next;
        free(l2);
        l2 = iter;
    }
    return 0;
}
