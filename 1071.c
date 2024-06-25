#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int gcd(int m, int n);
char* gcdOfStrings(char* str1, char* str2);

int gcd(int m, int n)
{
    if (!m) return n;
    if (!n) return m;
    return m > n ? gcd(m % n, n) : gcd(m, n % m);
}

char* gcdOfStrings(char* str1, char* str2)
{
    int m = strlen(str1), n = strlen(str2), length = m + n + 1;
    str1 = realloc(str1, length * sizeof(char));
    str2 = realloc(str2, length * sizeof(char));
    if  (!str1 || !str2)    return NULL;
    /**
     * Consider gcd(str1, str2) = s. s is a string.
     * Since str1 and str2 are divisible by s,
     * we can assume str1 = xs and str2 = ys.
     * Both x and y are integer.
     * Thus, str1 + str2 = (x + y)s = (y + x)s = str2 + str1.
     * Therefore, if str1 + str2 != str2 + str1,
     * the assumption must be wrong i.e.
     * s is an empty string, so that both x and y are infinite.
     * Therefore, an empty string is returned here.
     */
    str1 = strncat(str1, str2, n);
    str2 = strncat(str2, str1, m);
    if (strcmp(str1, str2)) return "";
    /**
     * Since s exists and isn't empty, 
     * s is a prefix for both str1 and str2.
     * Thus, the answer is str1[0:strlen(s)] or str2[0:strlen(s)].
     * Now the question is, what's strlen(s)?
     * Since gcd(str1, str2) = s,
     * strlen(s) must be the greatest common divisor of 
     * strlen(str1) and strlen(str2).
     */
    else    str1[gcd(m, n)] = '\0';
    return str1;
}

int main()
{
    char *str1 = (char *)calloc(7, sizeof(char)), *str2 = (char *)calloc(5, sizeof(char));
    str1 = (char *)memcpy(str1, "ABABAB", 6);
    str2 = (char *)memcpy(str2, "ABAB", 4);
    printf("%s\n", gcdOfStrings(str1, str2));
    free(str1);
    free(str2);
    return 0;
}
