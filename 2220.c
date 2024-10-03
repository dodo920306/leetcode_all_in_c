#include <stdio.h>

int minBitFlips(int, int);

int minBitFlips(int start, int goal)
{
    int res = 0, diff = start ^ goal;
    while (diff) {
        res++;
        diff &= diff - 1;
    }
    return res;
}

int main()
{
    printf("%d\n", minBitFlips(10, 7));
    return 0;
}
