#include <stdio.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *mergeInBetween(struct ListNode *list1, int a, int b, struct ListNode *list2);

struct ListNode *mergeInBetween(struct ListNode *list1, int a, int b, struct ListNode *list2)
{
    struct ListNode *remove_head = list1, *remove_end;
    a--;
    b -= a;
    while (a--)
        remove_head = remove_head->next;
    remove_end = remove_head->next;
    while (b--)
        remove_end = remove_end->next;

    remove_head->next = list2;
    while (list2->next) list2 = list2->next;
    list2->next = remove_end;
    return list1;
}

int main()
{
    struct ListNode node6 = {6, NULL}, node5 = {5, &node6}, node4 = {4, &node5}, node3 = {3, &node4}, node2 = {2, &node3}, node1 = {1, &node2}, node0 = {0, &node1}, node1000004 = {1000004, NULL}, node1000003 = {1000003, &node1000004}, node1000002 = {1000002, &node1000003}, node1000001 = {1000001, &node1000002}, node1000000 = {1000000, &node1000001}, list1[] = {node0, node1, node2, node3, node4, node5, node6}, list2[] = {node1000000, node1000001, node1000002, node1000003, node1000004}, *res = mergeInBetween(list1, 2, 5, list2);
    while (res) {
        printf("%d ", res->val);
        res = res->next;
    }
    printf("\n");
    return 0;
}
