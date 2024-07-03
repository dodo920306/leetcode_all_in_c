#include <stdio.h>
#include <string.h>

char *removeStars(char* s);

char *removeStars(char* s)
{
    int length = strlen(s), sSize = 0;
    for (int i = 0; i < length; i++)
        if (s[i] == '*')
            sSize--;
        else
            s[sSize++] = s[i];
    s[sSize] = '\0';
    return s;
}

int main()
{
    char s[] = "leet**cod*e";
    printf("%s\n", removeStars(s));
    return 0;
}
