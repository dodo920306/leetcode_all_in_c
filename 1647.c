#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void * a, const void * b);
int minDeletions(char * s);

int main()
{
    char s[9] = "ceabaacb";
    printf("%d\n", minDeletions(s));
    
}

int cmp(const void * a, const void * b)
{
    /* reverse */
    return (*(int*)b - *(int*)a);
}

int minDeletions(char * s)
{
    int length = strlen(s), freq[26], ans = 0;
    for (int i = 0; i < 26; i++) {
        freq[i] = 0;
    }
    for (int i = 0; i < length; i++) {
        freq[s[i] - 'a']++;
    }
    qsort(freq, 26, sizeof(int), cmp);
    for (int i = 1; i < 26; i++) {
        /* Here we try to make freq strictly decreasing.
         * Suppose that the freq is {2, 2, 2, 0, 0, 0, ...} like s = "abcabc".
         * After a loop, the freq = {2, 1, 2, 0, 0, 0, ...}.
         * As you can see, a situation freq[i] > freq[i - 1] may happened, 
         * so we adjust the loop condition from freq[i] == freq[i - 1] to freq[i] > freq[i - 1]
         * to keep the original reversed sorted array sorted.
         */
        while (freq[i] && freq[i] >= freq[i - 1]) {
            freq[i]--;
            ans++;
        }
    }
    return ans;
}
