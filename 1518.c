#include <stdio.h>

int numWaterBottles(int numBottles, int numExchange);

int numWaterBottles(int numBottles, int numExchange)
{
    int res = numBottles, quotient, remainder;
    do {
        quotient = numBottles / numExchange;
        remainder = numBottles % numExchange;
        res += quotient;
        numBottles = quotient + remainder;
    } while (quotient);
    return res;
}

int main()
{
    printf("%d\n", numWaterBottles(15, 4));
    return 0;
}
