#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isSubsequence(char *s, char *t);

bool isSubsequence(char *s, char *t)
{
    int i = 0, sLength = strlen(s), tLength = strlen(t);
    if (sLength) {
        for (int j = 0; j < tLength; j++)
            if (s[i] == t[j]) {
                i++;
                if (i == sLength)
                    return true;
            }
        return false;
    }
    return true;
}

int main()
{
    printf("%s\n", isSubsequence("abc", "ahbgdc") ? "true" : "false");
    return 0;
}
