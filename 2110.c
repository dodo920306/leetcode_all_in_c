#include <stdio.h>

long long getDescentPeriods(int* prices, int pricesSize);

int main()
{
    int prices[] = {3, 2, 1, 4};
    printf("%lld\n", getDescentPeriods(prices, 4));
    return 0;
}

long long getDescentPeriods(int* prices, int pricesSize)
{
    long long res = 0;
    for (int i = 0, j = 0; j < pricesSize;) {
        if (i == j || prices[j] - prices[j - 1] == -1) {
            j++;
            res += j - i;
        }
        else {
            i = j;
        }
    }
    return res;
}
