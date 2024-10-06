#include <stdio.h>
#include <stdlib.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode {
    int val;
    struct ListNode *next;
};
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int getListSize(struct ListNode *head)
{
    int res = 0;
    for (struct ListNode *iter = head; iter; iter = iter->next)
        res++;
    return res;
}

struct ListNode **splitListToParts(struct ListNode *head, int k, int *returnSize)
{
    int length = getListSize(head), shortestPartLength = length / k - 1, longestPartLength = shortestPartLength + 1, numOfLongestParts = length % k;
    struct ListNode **res = (struct ListNode **)calloc(k, sizeof(struct ListNode *)), *next;
    *returnSize = 0;
    if (!res) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    while (numOfLongestParts--) {
        res[(*returnSize)++] = head;
        for (int i = 0; i < longestPartLength; i++)
            head = head->next;
        next = head->next;
        head->next = NULL;
        head = next;
    }
    if (shortestPartLength >= 0)
        while ((*returnSize) < k) {
            res[(*returnSize)++] = head;
            for (int i = 0; i < shortestPartLength; i++)
                head = head->next;
            next = head->next;
            head->next = NULL;
            head = next;
        }

    *returnSize = k;
    return res;
}

int main()
{
    /* 1,2,3,4,5,6,7,8,9,10 */
    int returnSize = 0;
    struct ListNode node10 = {10, NULL}, \
                    node9 = {9, &node10}, \
                    node8 = {8, &node9}, \
                    node7 = {7, &node8}, \
                    node6 = {6, &node7}, \
                    node5 = {5, &node6}, \
                    node4 = {4, &node5}, \
                    node3 = {3, &node4}, \
                    node2 = {2, &node3}, \
                    node1 = {1, &node2}, \
                    **res = splitListToParts(&node1, 3, &returnSize);
    for (int i = 0; i < returnSize; i++) {
        if (!(res[i])) {
            continue;
            printf("\n");
        }

        printf("%d", res[i]->val);
        for (struct ListNode *iter = res[i]->next; iter; iter = iter->next) {
            printf(" -> %d", iter->val);
        }
        printf("\n");
    }
    return 0;
}
