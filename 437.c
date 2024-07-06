#include <stdio.h>
#include "uthash/include/uthash.h"

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct Table {
    long key;
    int value;
    UT_hash_handle hh;
};

void _pathSum(struct TreeNode *root, int targetSum, long currentSum, int *count, struct Table *table);
int pathSum(struct TreeNode *root, int targetSum);

void _pathSum(struct TreeNode *root, int targetSum, long currentSum, int *count, struct Table *table)
{
    long key;
    struct Table *t;
    currentSum += root->val;
    if (currentSum == targetSum)
        (*count)++;
    /**
     * currentSum only increases not decreases.
     * It only record the sum from the root to the current node.
     * For the end of those path sums with only middle nodes,
     * currentSum = targetSum + prefixSum where prefixSum
     * is the sum from the root to the beginning of the
     * middle path.
     * Thus, these paths exist iff prefixSums exist
     * iff (currentSum - targetSum)s exist.
     * If they do exist, add them to the count.
     */
    key = currentSum - targetSum;
    HASH_FIND(hh, table, &key, sizeof(long), t);
    if (t)  (*count) += t->value;
    /**
     * check if currentSum already exists.
     * If not, create it.
     */
    HASH_FIND(hh, table, &currentSum, sizeof(long), t);
    if (!t) {
        if (!(t = (struct Table *)malloc(sizeof(struct Table))))
            return;
        t->key = currentSum;
        HASH_ADD(hh, table, key, sizeof(long), t);
        t->value = 0;
    }
    t->value++;
    if (root->left)
        _pathSum(root->left, targetSum, currentSum, count, table);
    if (root->right)
        _pathSum(root->right, targetSum, currentSum, count, table);
    /**
     * For those nodes below this node and in this subtree, there exists a prefixSum as the currentSum here.
     * However, for those not in this subtree, the path shouldn't be counted in,
     * and directly return will make this path still available to others.
     * While only descendants of the current node can have this path as a prefix,
     * this path should be deleted before return to other subtrees.
     */
    t->value--;
}

int pathSum(struct TreeNode *root, int targetSum)
{
    struct Table *table = NULL, *i, *tmp;
    int res = 0;
    if (root)
        _pathSum(root, targetSum, 0, &res, table); 
    HASH_ITER(hh, table, i, tmp) {
        HASH_DEL(table, i);
        free(i);
    }
    return res;
}

int main()
{
    struct TreeNode node8 = {1, NULL, NULL}, node7 = {-2, NULL, NULL}, node6 = {3, NULL, NULL}, node5 = {11, NULL, NULL}, node4 = {2, NULL, &node8}, node3 = {3, &node6, &node7}, node2 = {-3, NULL, &node5}, node1 = {5, &node3, &node4}, root = {10, &node1, &node2};
    printf("%d\n", pathSum(&root, 8));
    return 0;
}
