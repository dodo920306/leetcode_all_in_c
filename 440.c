#include <stdio.h>

int numOfChildrenInLexicographicalTree(long long, long);
int findKthNumber(int, int);

int numOfChildrenInLexicographicalTree(long long n, long parent)
{
    long long res = 0, rightSibling = parent + 1;
    while (rightSibling <= n) {
        res += rightSibling - parent;
        parent *= 10;
        rightSibling *= 10;
    }
    n -= parent;

    return n >= 0 ? res + n + 1 : res;
}

int findKthNumber(int n, int k)
{
    long long res = 1, numOfSteps;
    k--;
    while (k) {
        numOfSteps = numOfChildrenInLexicographicalTree(n, res);
        if (numOfSteps <= k) {
            res++;
            k -= numOfSteps;
        }
        else {
            res *= 10;
            k--;
        }
    }

    return res;
}

int main()
{
    printf("%d\n", findKthNumber(13, 2));
    return 0;
}
