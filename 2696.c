#include <stdio.h>

int minLength(char *);

int minLength(char *s)
{
    int res = 1;
    for (int i = 1; s[i]; i++)
        if (res && ((s[res - 1] == 'A' && s[i] == 'B') || (s[res - 1] == 'C' && s[i] == 'D')))
            res--;
        else
            s[res++] = s[i];

    return res;
}

int main()
{
    char s[] = "ABFCACDB";
    printf("%d\n", minLength(s));
    return 0;
}
