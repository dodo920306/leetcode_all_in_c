#include <stdio.h>

int findTheWinner(int n, int k);

int findTheWinner(int n, int k)
{
    /**
     * If there is only one node, it's the winner.
     *
     * If not, the problem shrink into the same problem with n - 1 nodes.
     * The only difference there are the position of the beginning, from 1 to k + 1,
     * so we add k every recursion.
     *
     * Finally, since it's a circular list, all operations have to be done
     * under modulo n.
     * To do this, we have to minus 1 from the previous result first.
     * Then add it back after the modulo.
     */
    return (n - 1 ? (findTheWinner(n - 1, k) + k - 1) % n : 0) + 1;
}

int main()
{
    printf("%d\n", findTheWinner(5, 2));
    return 0;
}
