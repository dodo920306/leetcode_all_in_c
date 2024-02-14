#include <stdio.h>
#include <stdlib.h>

int maxProfit(int* prices, int pricesSize);

int maxProfit(int* prices, int pricesSize)
{
    int ans = 0;
    for (int i = 1, index_of_the_cheapest = 0, diff = 0, sign = ((sizeof(int) << 3) - 1); i < pricesSize; i++) {
        diff = prices[i] - prices[index_of_the_cheapest];
        if (diff >> sign)
            index_of_the_cheapest = i;
        else if (diff > ans)
            ans = diff;
    }
    return ans;
}

int main()
{
    int prices[6] = {7, 1, 5, 3, 6, 4}, pricesSize = 6;
    printf("%d\n", maxProfit(prices, pricesSize));
}
