#include <stdio.h>
#include <string.h>

#define UPDATE_MAXIMUM(max, current) \
    /** \
     * This macro will update the value of max, \
     * so a pointer must be sent in as max. \
     */ \
    do { \
        int *_max = (max), _current = (current); \
        if (*_max < _current) { \
            *_max = _current; \
        } \
    } while(0)

short lowercaseLetterToVowelBitmask(char);
int findTheLongestSubstring(char *);

short lowercaseLetterToVowelBitmask(char c)
{
    switch (c) {
        case 'a':
            return 1;
        case 'e':
            return 2;
        case 'i':
            return 4;
        case 'o':
            return 8;
        case 'u':
            return 16;
        default:
            return 0;
    }
}

int findTheLongestSubstring(char *s)
{
    int res = 0, xorToIndex[32];

    for (int i = 0; i < 32; i++)
        xorToIndex[i] = -1;

    for (int i = 0, length = strlen(s), xor = 0; i < length; i++) {
        xor ^= lowercaseLetterToVowelBitmask(s[i]);
        if (xor && xorToIndex[xor] == -1)
            xorToIndex[xor] = i;
        else
            UPDATE_MAXIMUM(&res, i - xorToIndex[xor]);
    }

    return res;
}

int main()
{
    printf("%d\n", findTheLongestSubstring("eleetminicoworoep"));
    return 0;
}
