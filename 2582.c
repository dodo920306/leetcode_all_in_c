#include <stdio.h>

int passThePillow(int n, int time);

int passThePillow(int n, int time)
{
    if (time / (n - 1) % 2)
        return n - time % (n - 1);
    else
        return time % (n - 1) + 1;
}

int main()
{
    printf("%d\n", passThePillow(4, 5));
    return 0;
}
