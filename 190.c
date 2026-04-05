#include <stdio.h>

int reverseBits(int n);

int main() {
    printf("%d\n", reverseBits(43261596));
    printf("%d\n", reverseBits(2147483644));
    return 0;
}

int reverseBits(int n) {
    int res = 0;
    for (int i = 0; i < 31; i++) {
        /* copy the rightest bit of n to the rightest bit of res */
        res |= (n & 1);
        /* move n to the right to get the next left bit */
        n >>= 1;
        /* move res to the left to receive the next rightest bit of n */
        res <<= 1;
    }
    return res | (n & 1);
}
