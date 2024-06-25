#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool isVowel(char c)
{
    return (c == 'a') || (c == 'e') || (c == 'i') || (c == 'o') || (c == 'u') || (c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') || (c == 'U');
}

char* reverseVowels(char* s) {
    int i = 0, j = strlen(s) - 1;
    char swap_temp;
    while (i < j) {
        if (!isVowel(s[i]))    i++;
        if (!isVowel(s[j]))    j--;
        if (isVowel(s[i]) && isVowel(s[j])) {
            swap_temp = s[i];
            s[i] = s[j];
            s[j] = swap_temp;
            i++;
            j--;
        }
    }
    return s;
}

int main()
{
    char s[] = "hello";
    printf("%s\n", reverseVowels(s));
    return 0;
}
