#include <stdio.h>

int rangeBitwiseAnd(int left, int right);

int rangeBitwiseAnd(int left, int right)
{
    /**
     * If right has a same prefix as left, this part won't change through left to right.
     * e.g. 00000000 00000000 00000000 00000101
     *      00000000 00000000 00000000 00000111
     * The part starting from MSB to the third bit from the left is same, 
     * so the result will be
     *      00000000 00000000 00000000 000001XX
     * because this part won't change for integers belong to [left, right].
     * 
     * Moreover, the suffix of the result is all 0 since:
     * 
     * Because the two integers differ from each other for the suffix, 
     * the MSB of the suffix must be 0 and 1 respectively,
     * or the bit will belong to the prefix.
     * Since left <= right, the suffix is
     *      0XXXX...
     *      1YYYY...
     * This means that no matter left and right are, the number having the same prefix as them
     * and 01111... (all Xs are 1s) as suffix must exist in [left, right] if they're different 
     * i.e. they have different suffices.
     * Similarly, the number having the same prefix as them and 10000... (all Ys are 0s) as suffix 
     * must exist in [left, right] if they have different suffices.
     * Like in the example above, 00000000 00000000 00000000 00000101 and 00000000 00000000 00000000 00000110 
     * indeed belong to [left, right],
     * and their existence can make the suffix of the result are all 0s.
     * Therefore, we can get the result of the example 00000000 00000000 00000000 00000100.
     * 
     */
    int suffix_length = 0;
    while (left != right) {
        left >>= 1;
        right >>= 1;
        suffix_length++;
    }
    return left << suffix_length;
}

int main()
{
    printf("%d", rangeBitwiseAnd(5, 7));
    return 0;
}
