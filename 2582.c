#include <stdio.h>

int passThePillow(int n, int time);

int passThePillow(int n, int time)
{
    /**
     * n - 1: number of steps for a round.
     * For example, it takes three steps for four people to
     * pass a pillow from the first person to the last.
     *
     * time / (n - 1): number of round.
     * If this is odd, it's the last person (n-th) that has the pillow.
     * Otherwise, it's the first person.
     *
     * time % (n - 1): number of steps left.
     *
     * Therefore, the result is either n - time % (n - 1) or 1 + time % (n - 1).
     */
    if (time / (n - 1) % 2)
        return n - time % (n - 1);
    else
        return 1 + time % (n - 1);
}

int main()
{
    printf("%d\n", passThePillow(4, 5));
    return 0;
}
