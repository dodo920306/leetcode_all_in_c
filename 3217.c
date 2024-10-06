#include <stdio.h>
#include "uthash/include/uthash.h"

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

struct intSet {
    int key;
    UT_hash_handle hh;
};

struct ListNode *modifiedList(int *, int, struct ListNode *);

struct ListNode *modifiedList(int *nums, int numsSize, struct ListNode *head)
{
    struct intSet *set = NULL, *element = NULL, *isIn = NULL;

    for (int i = 0; i < numsSize; i++) {
        HASH_FIND_INT(set, &(nums[i]), isIn);
        if (isIn)   continue;

        element = (struct intSet *)malloc(sizeof(struct intSet));
        if (!element) {
            fprintf(stderr, "Error: Memory Allocation Failed.");
            return NULL;
        }

        element->key = nums[i];
        HASH_ADD_INT(set, key, element);
    }

    for (struct ListNode **iter = &head, *deleted; *iter;) {
        HASH_FIND_INT(set, &((*iter)->val), isIn);
        if (isIn) {
            deleted = *iter;
            *iter = (*iter)->next;
            free(deleted);
        }
        else
            iter = &((*iter)->next);
    }

    HASH_ITER(hh, set, element, isIn) {
        free(element);
    }

    return head;
}

int main()
{
    int nums[] = {1, 2, 3};
    struct ListNode *node5 = (struct ListNode *)malloc(sizeof(struct ListNode)), \
                    *node4 = (struct ListNode *)malloc(sizeof(struct ListNode)), \
                    *node3 = (struct ListNode *)malloc(sizeof(struct ListNode)), \
                    *node2 = (struct ListNode *)malloc(sizeof(struct ListNode)), \
                    *node1 = (struct ListNode *)malloc(sizeof(struct ListNode)), \
                    *res = NULL;
    if (!(node1 && node2 && node3 && node4 && node5)) {
        fprintf(stderr, "Error: Memory Allocation Failed");
        return -1;
    }
    node1->val = 1;
    node1->next = node2;

    node2->val = 2;
    node2->next = node3;

    node3->val = 3;
    node3->next = node4;

    node4->val = 4;
    node4->next = node5;

    node5->val = 5;
    node5->next = NULL;

    res = modifiedList(nums, 3, node1);

    if (res)    printf("%d", res->val);
    for (struct ListNode *iter = res->next, *next = iter->next; iter; iter = next) {
        next = iter->next;
        printf(" -> %d", iter->val);
        free(iter);
    }
    free(res);
    printf("\n");
    return 0;
}
