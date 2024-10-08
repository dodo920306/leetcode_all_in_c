#include <stdio.h>

int minSwaps(char *);

int minSwaps(char *s)
{
    int res = 0;
    for (int i = 0; s[i]; i++)
        if (s[i] == '[')    res++;
        else if (res)   res--;
    return (res + 1) / 2;
}

int main()
{
    printf("%d\n", minSwaps("]]][[["));
    return 0;
}
