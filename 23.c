#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/**
 * The solution comes from https://hackmd.io/@sysprog/c-linked-list.
 * Please consider referring to that before contributing this file.
 */

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2);
struct ListNode *mergeKLists(struct ListNode **lists, int listsSize);

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    /* indir is declared with head. Thus, head gets updated every time indir gets updated. */
    struct ListNode *head = NULL, **indir = &head;
    for (struct ListNode **iter = NULL; list1 && list2; *iter = (*iter)->next) { 
        /* update what the new node should be every time i.e. update what iter points directly. */
        iter = (list1->val < list2->val) ? &(list1) : &(list2);
        /* update the new list */
        *indir = *iter;
        /* move the new list ahead */
        indir = &((*indir)->next);
        /**
         * In the end of every loop, indir will be updated as the new next address,
         * but what's in iter won't get changed.
         * Instead, what it points (list1 or list2) is changed as the next node in the pointed list.
         */
    }
    /* transform into uintptr_t first for the bitwise or. */
    *indir = (struct ListNode *)((uintptr_t) list1 | (uintptr_t) list2);
    return head;
}

struct ListNode *mergeKLists(struct ListNode **lists, int listsSize)
{
    if (!listsSize) return NULL;
    if (listsSize != 1){
        for (int i = 1; i < listsSize; i *= 2) {
            for (int j = 0; i + j < listsSize; j += 2 * i) {
                lists[j] = mergeTwoLists(lists[j], lists[i + j]);
            }
        }
    }
    return *lists;
}

int main()
{
    struct ListNode node2 = {.val = 5, .next = NULL}, node4 = {.val = 4, .next = NULL}, node5 = {.val = 6, .next = NULL}, node1 = {.val = 4, .next = &node2}, node3 = {.val = 3, .next = &node4}, list1 = {.val = 1, .next = &node1}, list2 = {.val = 1, .next = &node3}, list3 = {.val = 2, .next = &node5}, **lists = (struct ListNode **)malloc(3 * sizeof(struct ListNode *)), *res;
    if (!lists) {
        perror("Error");
        return 1;
    }
    lists[0] = &list1;
    lists[1] = &list2;
    lists[2] = &list3;

    res = mergeKLists(lists, 3);
    while (res)
    {
        printf("%d ", res->val);
        res = res->next;
    }
    free(res);
    return 0;
}
