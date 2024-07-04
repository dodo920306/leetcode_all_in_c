#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *oddEvenList(struct ListNode *head);

struct ListNode *oddEvenList(struct ListNode *head)
{
    if (head && head->next) {
        struct ListNode *i = head, *j = head->next, *even_head = j;
        while (j && j->next) {
            i->next = j->next;
            i = i->next;
            j->next = i->next;
            j = j->next;
        }
        i->next = even_head;
    }
    return head;
}

int main()
{
    struct ListNode node6 = {7, NULL}, node5 = {4, &node6}, node4 = {6, &node5}, node3 = {5, &node4}, node2 = {3, &node3}, node1 = {1, &node2}, head = {2, &node1}, *res = oddEvenList(&head);
    printf("[%d", res->val);
    res = res->next;
    while (res) {
        printf(", %d", res->val);
        res = res->next;
    }
    printf("]\n");
    return 0;
}
