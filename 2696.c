#include <stdio.h>
#include <string.h>

int minLength(char *s)
{
    int res = 1;
    for (int i = 1, length = strlen(s); i < length; i++)
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
