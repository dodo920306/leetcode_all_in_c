#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode* reverseBetween(struct ListNode* head, int left, int right);

int main()
{
    struct ListNode *head, *node1, *node2, *node3, *node4;
    head = (struct ListNode *)malloc(sizeof(struct ListNode));
    node1 = (struct ListNode *)malloc(sizeof(struct ListNode));
    node2 = (struct ListNode *)malloc(sizeof(struct ListNode));
    node3 = (struct ListNode *)malloc(sizeof(struct ListNode));
    node4 = (struct ListNode *)malloc(sizeof(struct ListNode));

    head->val = 1;
    head->next = node1;
    node1->val = 2;
    node1->next = (struct ListNode *)NULL;
    // node1->next = node2;
    // node2->val = 3;
    // node2->next = node3;
    // node3->val = 4;
    // node3->next = node4;
    // node4->val = 5;
    // node4->next = (struct ListNode *)NULL;
    head = reverseBetween(head, 1, 2);
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
}

struct ListNode* reverseBetween(struct ListNode* head, int left, int right)
{
    if (left != right) {
        int length = right - left + 1, top = 0;
        struct ListNode *fakehead;
        fakehead = (struct ListNode *)malloc(sizeof(struct ListNode));
        fakehead->next = head;
        struct ListNode **stack, *left_ptr = fakehead, *itr_ptr;
        stack = (struct ListNode **)malloc(length * sizeof(struct ListNode *));
        for (int i = 0; i < left - 1; i++) {
            left_ptr = left_ptr->next;
        }
        /* left_ptr stop at the last one node before left node. That's why there's a fakehead -- make a place for left_ptr to stop. */
        itr_ptr = left_ptr;

        while (top != length) {
            itr_ptr = itr_ptr->next;
            stack[top++] = itr_ptr;
        }
        itr_ptr = itr_ptr->next;
        /* itr_ptr now is at head of nodes on the right side of right node even if it's NULL. */

        while (top-- > 0) {
            left_ptr->next = stack[top];
            left_ptr = left_ptr->next;
        }
        left_ptr->next = itr_ptr;

        head = fakehead->next;
        /* In the reverse process that involving moving head around,
         * the pointer head could not be at head of the linked list any more.
         * In contrast, since fakehead isn't originally a part of the list, it's impossible that it could move,
         * so it'll always point to the real head of the list.
         */
    }
    return head;
}
