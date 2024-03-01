#include <stdio.h>
#include <string.h>

char *maximumOddBinaryNumber(char *s);

char *maximumOddBinaryNumber(char *s)
{
    int bits = strlen(s), ones = 0, i = 0;
    while(i < bits) {
        if (s[i] - '0') ones++;
        s[i++] = '0';
    }
    i = 0;
    ones--;
    bits--;
    while (ones--)   s[i++] = '1';
    s[bits] = '1';
    return s;
}

int main() {
    char s[] = "0101";
    printf("%s", maximumOddBinaryNumber(s));
    return 0;
}
