#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define NUM_OF_LETTERS 26

struct intStr {
    int length, *numOfLetters, *strToInt;
};

bool areEqualIntArrays(int *arr1, int *arr2, int length);
struct intStr *newIntString(char *s);
void freeIntString(struct intStr *str);
bool checkInclusion(char *s1, char *s2);

bool areEqualIntArrays(int *arr1, int *arr2, int length)
{
    for (int i = 0; i < length; i++)
        if (arr1[i] != arr2[i]) return false;
    return true;
}

struct intStr *newIntString(char *s)
{
    struct intStr *str = (struct intStr *)malloc(sizeof(struct intStr));
    if (!str)   return NULL;

    str->numOfLetters = (int *)calloc(NUM_OF_LETTERS, sizeof(int));
    if (!(str->numOfLetters))   return NULL;

    str->length = strlen(s);
    str->strToInt = (int *)malloc((str->length) * sizeof(int));
    if (!(str->strToInt))    return NULL;

    for (int i = 0; i < str->length; i++)
        str->strToInt[i] = s[i] - 'a';

    return str;
}

void freeIntString(struct intStr *str)
{
    free(str->strToInt);
    free(str->numOfLetters);
    free(str);
}

bool checkInclusion(char *s1, char *s2)
{
    struct intStr *str1 = newIntString(s1), *str2 = newIntString(s2);
    if (!(str1 && str2))    return false;
    if (str2->length < str1->length)  return false;

    for (int i = 0; i < str1->length; i++) {
        str1->numOfLetters[str1->strToInt[i]]++;
        str2->numOfLetters[str2->strToInt[i]]++;
    }

    if (areEqualIntArrays(str1->numOfLetters, str2->numOfLetters, NUM_OF_LETTERS)) {
        freeIntString(str1);
        freeIntString(str2);
        return true;
    }

    for (int l = 0, r = str1->length; r < str2->length; r++) {
        str2->numOfLetters[str2->strToInt[l]]--;
        str2->numOfLetters[str2->strToInt[r]]++;

        if (areEqualIntArrays(str1->numOfLetters, str2->numOfLetters, NUM_OF_LETTERS)) {
            freeIntString(str1);
            freeIntString(str2);
            return true;
        }

        l++;
    }

    freeIntString(str1);
    freeIntString(str2);
    return false;
}

int main()
{
    printf("%s\n", checkInclusion("ab", "eidbaooo") ? "true" : "false");
    return 0;
}
