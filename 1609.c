#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

/**
 * This number was obtained through experiments.
 * If you can't pass the question, it means LeetCode has updated their test inputs, 
 * so please increase the number and report it.
 */
#define MAXIMUM_NUMBER_OF_NODE_PER_LEVEL 4904

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

bool isEvenOddTree(struct TreeNode *root);

bool isEvenOddTree(struct TreeNode *root)
{
    /**
     * stack1 is for the reversal next level we need to process 
     * while stack2 is for the current level we are processing.
     *
     * Use different stacks so that we can focus on the current level
     * while recording the next level.
     * 
     * The value of the minimum node is set as 0 to prevent overflow by subtractions.
     */
    struct TreeNode min_node = {.val = 0, .left = NULL, .right = NULL}, max_node = {.val = INT_MAX, .left = NULL, .right = NULL}, *stack1[MAXIMUM_NUMBER_OF_NODE_PER_LEVEL], *stack2[MAXIMUM_NUMBER_OF_NODE_PER_LEVEL], *top;
    int size1 = 1, size2 = 0, level = 0, sign = (sizeof(int) * CHAR_BIT) - 1;

    *stack1 = root;
    while (size1) {
        /* top is a imaginary leftmost node per level. */
        top = (level & 1) ? &max_node : &min_node;
        while (size1--) {
            /**
             * The parity of the elements and the index of the level shouldn't be the same
             * i.e. they shouldn't have the same LSB
             * i.e. the LSB of the result of xor of them should be 1
             * i.e. if that's 0, return false.
             */
            if (!((stack1[size1]->val ^ level) & 1)) return false;

            /* read the current level from right to left */
            stack2[size2++] = stack1[size1];
        }
        /**
         * By the end of the last loop, size1 will be turned from 0 to -1
         * so we need to add it back.
         */
        size1++;
        while (size2--) {
            /**
             * Since the elements should be in the strict order,
             * once there are same elements, something was wrong.
             * 
             * If the index of the level is odd,
             * i.e its LSB is 1,
             * the last node should always be bigger than the current one,
             * i.e. the MSB of their difference should be 0.
             * i.e. the result of keep shifting their difference from left to right should be 0x00
             * i.e. the result of not of keep shifting their difference from left to right should be 1.
             * vice versa,
             * so the xor of that and the LSB of the index should always be 0 (same),
             * or something was wrong.
             */
            if ((top->val == stack2[size2]->val) || ((level & 1) ^ !((top->val - stack2[size2]->val) >> sign)))   return false;
            /* read the current level from left to right */
            top = stack2[size2];
            /* read the next level from left to right */
            if (top->left)
                stack1[size1++] = top->left;
            if (top->right)
                stack1[size1++] = top->right;
        }
        /**
         * By the end of the last loop, size2 will be turned from 0 to -1
         * so we need to add it back.
         */
        size2++;
        level++;
    }
    /**
     * To escape the loop:
     * size1 is 0 => No next level yet
     * size2 is 0 => No more node on the left this level
     * top->left and right are NULL => No next level ever
     *
     * => the result
     */
    return true;
}

int main()
{
    struct TreeNode node1, node2, node3, node4, node5, node6, node7, node8, node9, node10;

    node1.val = 1;
    node2.val = 10;
    node3.val = 4;
    node4.val = 3;
    node5.val = 7;
    node6.val = 9;
    node7.val = 12;
    node8.val = 8;
    node9.val = 6;
    node10.val = 2;

    node1.left = &node2;
    node1.right = &node3;

    node2.left = &node4;
    node2.right = NULL;

    node3.left = &node5;
    node3.right = &node6;

    node4.left = &node7;
    node4.right = &node8;

    node5.left = &node9;
    node5.right = NULL;

    node6.left = NULL;
    node6.right = &node10;

    node7.left = NULL;
    node7.right = NULL;

    node8.left = NULL;
    node8.right = NULL;

    node9.left = NULL;
    node9.right = NULL;

    node10.left = NULL;
    node10.right = NULL;

    printf("%s", isEvenOddTree(&node1) ? "true" : "false");
    return 0;
}
