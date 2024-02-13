#include <stdio.h>

int firstUniqChar(char* s);

int firstUniqChar(char* s)
{
    int uni[26] = { 0 };
    char *start = s;
    while (*s != '\0') {
        uni[*s - 'a']++;
        s++;
    }
    s = start;
    while (*s != '\0') {
        if (uni[*s - 'a'] == 1) {
            return s - start;
        }
        s++;
    }
    return -1;
}

int main()
{
    char* s = "leetcode";
    printf("%d\n", firstUniqChar(s));
    return 0;
}
