#include <stdio.h>
/**
 * Add this if you want to malloc() and free() for nodes.
 * 
 * #include <stdlib.h>
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *removeNthFromEnd(struct ListNode *head, int n)
{
    struct ListNode **slow = &head, *fast = head, *next;
    while (n--)
        if (fast)
            fast = fast->next;
        else    return NULL;

    while (fast) {
        slow = &((*slow)->next);
        fast = fast->next;
    }

    next = ((*slow)->next);
    /**
     * Add this line if you want to release the space used by the removed node.
     * 
     * `free(*slow);`
     * 
     * This won't work here because we didn't get our nodes through malloc(),
     * but it should be there for LeetCode and the reality.
     */
    *slow = next;

    return head;
}

int main()
{
    struct ListNode node5 = {.val = 5, .next = NULL}, node4 = {.val = 4, .next = &node5}, node3 = {.val = 3, .next = &node4}, node2 = {.val = 2, .next = &node3}, node1 = {.val = 1, .next = &node2}, *res = removeNthFromEnd(&node1, 2);

    while (res) {
        printf("%d ", res->val);
        res = res->next;
    }
    return 0;
}
