#include <stdio.h>
#include <string.h>

int intConverter(int);
int charConverter(char);
int stringConverter(char *);
int getLucky(char *, int);

int intConverter(int k)
{
    int res = 0;
    while (k) {
        res += k % 10;
        k /= 10;
    }
    return res;
}

int charConverter(char c)
{
    return intConverter(c - '`');
}

int stringConverter(char *s)
{
    int res = 0;
    for (int i = 0, length = strlen(s); i < length; i++)
        res += charConverter(s[i]);
    return res;
}

int getLucky(char *s, int k)
{
    int res = stringConverter(s);
    k--;
    while (k--)
        res = intConverter(res);
    return res;
}

int main()
{
    printf("%d\n", getLucky("leetcode", 2));
    return 0;
}
