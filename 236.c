#include <stdio.h>
#include <stdint.h>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q);

struct TreeNode *lowestCommonAncestor(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q)
{
    struct TreeNode *left, *right;
    /* Whenever p or q is meet first, return. */
    if (root == p || root == q)
        return root;
    /* The lowest node that is p or q on the left subtree. */
    left = root->left ? lowestCommonAncestor(root->left, p, q) : NULL;
    /* The lowest node that is p or q on the right subtree. */
    right = root->right ? lowestCommonAncestor(root->right, p, q) : NULL;
    /**
     * If p and q are on the different subtrees, 
     * they must be the lowest node that is p or q on each subtree.
     *
     * In that case, root is the LCA.
     */
    if (left && right)
        return root;
    /**
     * If p and q are on the same subtree, 
     * the lower one of them must be the lowest node that is p or q on that subtree.
     *
     * In that case, it's the LCA
     *
     * Since (left && right) == false, either left or right is NULL,
     * and the other one needs to be returned.
     * 
     * Since NULL is false in boolean, 
     * simply use an or (|) can get the non-NULL one of these two.
     * 
     * Since op operations can't be applied on pointers,
     * cast them into unsigned numbers to allow them to be applied pure bitwise operations.
     * 
     * uintptr_t is used here because the size of pointers differs from computers to computers,
     * and `stdint.c` will make sure that the size of an uintptr_t is exactly the size of pointers
     * on each computer.
     * 
     * After being applied the or operation, cast the result back into a pointer to
     * allow it to be returned in this function.
     */
    return (struct TreeNode *)((uintptr_t)left | (uintptr_t)right);
}

int main()
{
    struct TreeNode node8 = {4, NULL, NULL}, node7 = {7, NULL, NULL}, node6 = {8, NULL, NULL}, node5 = {0, NULL, NULL}, node4 = {2, &node7, &node8}, node3 = {6, NULL, NULL}, node2 = {1, &node5, &node6}, node1 = {5, &node3, &node4}, head = {3, &node1, &node2};
    printf("%d\n", lowestCommonAncestor(&head, &node1, &node2)->val);
    return 0;
}
