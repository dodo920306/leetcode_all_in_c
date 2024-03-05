#include <stdio.h>
#include <string.h>

int minimumLength(char *s);

int minimumLength(char *s)
{
    int i = 0, j = strlen(s) - 1;
    char t;
    while (i < j) {
        /**
         * We can't allow i == j here because 
         * there is only one character left 
         * which doesn't belong to either prefix or suffix.
         */
        if (s[i] == s[j]) {
            t = s[j];
            /* We can allow i == j here to find the whole prefix and suffix. */
            while (i <= j && s[i] == t)   i++;
            while (i <= j && s[j] == t)   j--;
        }
        else    break;
    }
    return j - i + 1;
}

int main()
{
    printf("%d", minimumLength("aabccabba"));
    return 0;
}
