#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool *kidsWithCandies(int *candies, int candiesSize, int extraCandies, int *returnSize);

bool *kidsWithCandies(int *candies, int candiesSize, int extraCandies, int *returnSize)
{
    int greatest_number_of_candies = 0;
    bool *res = (bool *)calloc(candiesSize, sizeof(bool));
    if (!res)   return NULL;
    *returnSize = candiesSize;
    for (int i = 0; i < candiesSize; i++)   if (candies[i] > greatest_number_of_candies) greatest_number_of_candies = candies[i];
    for (int i = 0; i < candiesSize; i++)   if (candies[i] + extraCandies >= greatest_number_of_candies) res[i] = true;
    return res;
}

int main()
{
    int candies[] = {2, 3, 5, 1, 3}, returnSize;
    bool *res = kidsWithCandies(candies, 5, 3, &returnSize);
    returnSize--;
    printf("[");
    for (int i = 0; i < returnSize; i++)    printf("%s,", res[i] ? "true" : "false");
    printf("%s", res[returnSize] ? "true" : "false");
    printf("]\n");
    return 0;
}
