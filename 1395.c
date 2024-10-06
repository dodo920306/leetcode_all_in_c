#include <stdio.h>
#include <stdlib.h>

int lsb(int);
int maximum(int *, int);
void updateBIT(int *, int, int, int);
int getCumulativeFrequency(int *, int);

int lsb(int k)
{
    /**
     * In 2's complement, -k = ~k + 1.
     * Since k & ~k = 0,
     * k & -k = k & (~k + 1) will flip every bit under the least significant bit and itself
     * while remaining every bit above it as 0.
     *
     * e.g. k = xxx100, ~k = yyy011, -k = ~k + 1 = yyy100, x & y = 0.
     * Therefore, k & -k = 000100.
     */
    return k & -k;
}

int maximum(int *array, int n)
{
    int res = *array;
    for (int i = 1; i < n; i++)
        if (array[i] > res) res = array[i];

    return res;
}

void updateBIT(int *bit, int n, int index, int value)
{
    while (index < n) {
        bit[index] += value;
        /**
         * By adding the LSB, the index will become the nearest ancestor that
         * the original index is on its left subtree.
         * e.g. n = 13 (0-node is omitted)
         *                      8
         *                 /         \
         *                4           12
         *              /   \       /     \
         *             2     6     10      14
         *            / \   / \   /  \    /
         *           1   3 5   7 9    11 13
         *      5 + 1 = 6; 6 + 2 = 8; 8 + 8 = 16 > n.
         *      3 + 1 = 4; 4 + 4 = 8; 8 + 8 = 16 > n.
         * In a binary indexed tree, that's all of nodes an update will take place.
         */
        index += lsb(index);
    }
}

int getCumulativeFrequency(int *bit, int index)
{
    int res = 0;
    while (index > 0) {
        res += bit[index];
        /**
         * By subtracting the LSB, the index will become the nearest ancestor that
         * the original index is on its right subtree.
         * e.g. n = 13 (0-node is omitted)
         *                      8
         *                 /         \
         *                4           12
         *              /   \       /     \
         *             2     6     10      14
         *            / \   / \   /  \    /
         *           1   3 5   7 9    11 13
         *      13 - 1 = 12; 12 - 4 = 8; 8 - 8 = 0.
         *      7 - 1 = 6; 6 - 2 = 4; 4 - 4 = 0.
         * In a binary indexed tree, that's all of nodes should be considered when getting cumulative sums.
         */
        index -= lsb(index);
    }
    return res;
}

int numTeams(int *rating, int ratingSize)
{
    int maxRating = maximum(rating, ratingSize), \
        n = maxRating + 1, \
        *leftBIT = (int *)calloc(n, sizeof(int)), \
        *rightBIT = (int *)calloc(n, sizeof(int)), \
        res = 0;
    if (!(leftBIT && rightBIT)) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return -1;
    }

    for (int i = 0; i < ratingSize; i++)
        /**
         * In the beginning, all nodes are on the right.
         */
        updateBIT(rightBIT, n, rating[i], 1);

    for (int i = 0; i < ratingSize; i++) {
        /* pop the current node from the right */
        updateBIT(rightBIT, n, rating[i], -1);
        /**
         * getCumulativeFrequency(leftBIT, rating[i] - 1): the number of nodes smaller than rating[i] on the left.
         *
         * getCumulativeFrequency(rightBIT, maxRating) - getCumulativeFrequency(rightBIT, rating[i]):
         * the number of nodes larger than rating[i] on the right
         * (The number of nodes on the right - the number of nodes smaller than or equal to rating[i] on the right).
         *
         * getCumulativeFrequency(leftBIT, maxRating) - getCumulativeFrequency(leftBIT, rating[i]):
         * the number of nodes larger than rating[i] on the left
         * (The number of nodes on the left - the number of nodes smaller than or equal to rating[i] on the left).
         *
         * getCumulativeFrequency(rightBIT, rating[i] - 1): the number of nodes smaller than rating[i] on the right.
         */
        res += getCumulativeFrequency(leftBIT, rating[i] - 1) * (getCumulativeFrequency(rightBIT, maxRating) - getCumulativeFrequency(rightBIT, rating[i])) + (getCumulativeFrequency(leftBIT, maxRating) - getCumulativeFrequency(leftBIT, rating[i])) * getCumulativeFrequency(rightBIT, rating[i] - 1);
        /* push the current node to the left */
        updateBIT(leftBIT, n, rating[i], 1);
    }

    free(leftBIT);
    free(rightBIT);
    return res;
}

int main()
{
    int rating[] = {2, 5, 3, 4, 1};
    printf("%d\n", numTeams(rating, 5));
    return 0;
}
