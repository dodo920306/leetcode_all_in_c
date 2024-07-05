#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

int *nodesBetweenCriticalPoints(struct ListNode *head, int *returnSize);

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *nodesBetweenCriticalPoints(struct ListNode *head, int *returnSize)
{
    int criticalPointIndex[100000], size = 0, index = 2, *res;
    struct ListNode *a, *b, *c;
    if (!(res = (int *)malloc(2 * sizeof(int))))
        return NULL;
    *returnSize = 2;
    res[0] = -1;
    res[1] = -1;
    if (head && head->next && head->next->next) {
        a = head;
        b = a->next;
        c = b->next;
        while (a && b && c) {
            if ((b->val < a->val && b->val < c->val) || (b->val > a->val && b->val > c->val))
                criticalPointIndex[size++] = index;
            a = a->next;
            b = a->next;
            c = b->next;
            index++;
        }
        if (size > 1) {
            res[1] = criticalPointIndex[size - 1] - criticalPointIndex[0];
            res[0] = criticalPointIndex[1] - criticalPointIndex[0];
            for (int i = 2, diff; i < size; i++) {
                diff = criticalPointIndex[i] - criticalPointIndex[i - 1];
                if (res[0] > diff)  res[0] = diff;
            }
        }
    }
    return res;
}

int main()
{
    struct ListNode node6 = {2, NULL}, node5 = {1, &node6}, node4 = {5, &node5}, node3 = {2, &node4}, node2 = {1, &node3}, node1 = {3, &node2}, head = {5, &node1};
    int returnSize, *res = nodesBetweenCriticalPoints(&head, &returnSize);
    printf("[%d", res[0]);
    for (int i = 1; i < returnSize; i++)    printf(", %d", res[i]);
    printf("]\n");
    free(res);
    return 0;
}
