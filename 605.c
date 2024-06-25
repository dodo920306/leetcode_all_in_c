#include <stdio.h>
#include <stdbool.h>

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n);

bool canPlaceFlowers(int *flowerbed, int flowerbedSize, int n)
{
    flowerbedSize--;
    if (flowerbedSize) {
        /**
         * check if the left corner can be planted
         */
        if (!flowerbed[0] && !flowerbed[1]) {
            flowerbed[0] = 1;
            n--;
        }
        /**
         * check if the middle plots can be planted
         */
        for (int i = 1; i < flowerbedSize; i++) {
            if (!flowerbed[i] && !flowerbed[i - 1] && !flowerbed[i + 1]) {
                flowerbed[i] = 1;
                n--;
                if (!n) return true;
            }
        }
        /**
         * check if the right corner can be planted
         */
        if (!flowerbed[flowerbedSize - 1] && !flowerbed[flowerbedSize])
            n--;
        return (n <= 0);
    }
    else {
        /**
         * check if the only one plot is enough for flowers
         * that have to be planted or have been planted.
         */
        return (flowerbed[0] + n < 2);
    }
}

int main()
{
    int flowerbed[] = {1,0,0,0,1};
    printf("%s\n", canPlaceFlowers(flowerbed, 5, 1) ? "true" : "false");
    return 0;
}
