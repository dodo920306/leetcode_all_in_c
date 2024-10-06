#include <stdio.h>
#include <stdbool.h>
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
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

int *getLongestPrefixSuffix(int *arr, int arrSize)
{
    int *res = (int *)calloc(arrSize, sizeof(int)), previousLPS = 0;
    if (!res)   return NULL;

    for (int i = 1; i < arrSize;)
        if (arr[i] == arr[previousLPS]) {
            previousLPS++;
            res[i++] = previousLPS;
        }
        else if (previousLPS)
            previousLPS = res[previousLPS - 1];
        else
            i++;
    return res;
}

bool _isSubPath(struct TreeNode *node, int previousLPS, int *pattern, int *lps, int patternSize)
{
    bool isMatched = false;
    if (!node)
        return false;
    isMatched = (node->val == pattern[previousLPS]);
    if (previousLPS && !isMatched)
        return _isSubPath(node, lps[previousLPS - 1], pattern, lps, patternSize);

    previousLPS += isMatched;
    if (previousLPS == patternSize) return true;

    return _isSubPath(node->left, previousLPS, pattern, lps, patternSize) || 
           _isSubPath(node->right, previousLPS, pattern, lps, patternSize);
}

bool isSubPath(struct ListNode *head, struct TreeNode *root)
{
    int pattern[100], *lps, patternSize = 0;
    bool res = false;

    for (struct ListNode *iter = head; iter; iter = iter->next)
        pattern[patternSize++] = iter->val;

    lps = getLongestPrefixSuffix(pattern, patternSize);
    if (!lps) {
        fprintf(stderr, "Error: Memory Allocation Failed");
        return false;
    }
    res =  _isSubPath(root, 0, pattern, lps, patternSize);

    free(lps);
    return res;
}

int main()
{
    /* head = [4,2,8] */
    struct ListNode listNode3 = {8, NULL}, \
                    listNode2 = {2, &listNode3}, \
                    listNode1 = {4, &listNode2};
    /* root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3] */
    struct TreeNode treeNode10 = {3, NULL, NULL}, \
                    treeNode9 = {1, NULL, NULL}, \
                    treeNode8 = {8, &treeNode9, &treeNode10}, \
                    treeNode7 = {6, NULL, NULL}, \
                    treeNode6 = {1, NULL, NULL}, \
                    treeNode5 = {2, &treeNode7, &treeNode8}, \
                    treeNode4 = {2, &treeNode6, NULL}, \
                    treeNode3 = {4, &treeNode5, NULL}, \
                    treeNode2 = {4, NULL, &treeNode4}, \
                    treeNode1 = {1, &treeNode2, &treeNode3};
    printf("%s\n", isSubPath(&listNode1, &treeNode1) ? "true" : "false");
    return 0;
}
