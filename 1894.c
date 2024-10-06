#include <stdio.h>

int chalkReplacer(int *, int, int);

int chalkReplacer(int *chalk, int chalkSize, int k)
{
    if (*chalk > k) return 0;
    for (int i = 1; i < chalkSize; i++) {
        chalk[i] += chalk[i - 1];
        if (chalk[i] > k)   return i;
    }
    k %= chalk[chalkSize - 1];
    for (int i = 0; i < chalkSize; i++)
        if (chalk[i] > k)   return i;
    return -1;
}

int main()
{
    int chalk[] = {3, 4, 1, 2};
    printf("%d\n", chalkReplacer(chalk, 4, 25));
    return 0;
}
