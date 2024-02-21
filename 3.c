#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lengthOfLongestSubstring(char *s);

int lengthOfLongestSubstring(char *s)
{
    int *table = (int *)malloc(95 * sizeof(int));
    int length = strlen(s), res = 0;
    if (!table) {
        perror("Error");
        return INT_MIN;
    }

    for (int i = 0; i < 95; i++)    table[i] = -1;
    for (int i = 0, j = 0, window = 0; j < length; j++) {
        /* If s[j] has shown up in the window, we move i until it doesn't. */
        if (table[s[j] - ' '] >= i)
            i = table[s[j] - ' '] + 1;
        /**
         * Thus, the only s[j] in the window is s[j]. 
         * We update the position of this character every loop to get where it showed up last time.
         */
        table[s[j] - ' '] = j;
        /* update result with new length */
        window = j - i + 1;
        if (window > res)   res = window;
    }
    free(table);
    return res;
}

int main()
{
    char s[] = "abcabcbb";
    printf("%d", lengthOfLongestSubstring(s));
    return 0;
}
