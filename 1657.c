#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);
bool closeStrings(char *word1, char *word2);

int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

bool closeStrings(char *word1, char *word2)
{
    int length1 = strlen(word1), length2 = strlen(word2), table1[26] = {0}, table2[26] = {0};
    if (length1 != length2)
        return false;
    /**
     * Operation 1 allows the string to be freely reordered,
     * so only numbers of occurences need to be recorded.
     */
    for (int i = 0; i < length1; i++)
        table1[word1[i] - 'a']++;
    for (int i = 0; i < length2; i++)
        table2[word2[i] - 'a']++;
    /**
     * check if 2 words consist of same characters s.t.
     * it's possible to use operation 2 to make 2 words identical
     */
    for (int i = 0; i < 26; i++)
        /* use 2 not ops to convert integers into either 0 or 1 */
        if (!!table1[i] ^ !!table2[i])
            return false;
    qsort(table1, 26, sizeof(int), cmp);
    qsort(table2, 26, sizeof(int), cmp);
    /**
     * check if 2 words consist of same frequencies of characters s.t.
     * it's possible to use operation 2 to make 2 words identical
     */
    for (int i = 0; i < 26; i++)
        if (table1[i] != table2[i])
            return false;
    return true;
}

int main()
{
    printf("%s\n", closeStrings("cabbba", "abbccc") ? "true" : "false");
    return 0;
}
