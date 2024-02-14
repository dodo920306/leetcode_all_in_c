#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* minWindow(char *s, char *t);

char* minWindow(char *s, char *t)
{
    /**
     * A same letter can show up in t for multiple times.
     * Thus, an int array is used instead of a boolean array.
     */
    int *isInT = (int *)calloc(58, sizeof(int)), m = strlen(s), n = strlen(t), res_length = INT_MAX, from = 0;
    char *res;

    for (int i = 0; i < n; i++)
        isInT[(t[i] - 'A')]++;

    for (int head = 0, tail = 0, diff = 0; tail < m; tail++) {
        if (isInT[(s[tail] - 'A')]-- > 0)   n--;
        while (!n) {
            /* All letters in t are in s[head:tail], so s[head:tail] is currently a valid substring. */
            diff = (tail - head + 1);
            if (res_length > diff) {
                /* d(head, tail) < strlen(the original substring), so a new shorter valid substring shows up. */
                res_length = diff;
                from = head;
            }
            /* try moving head. add it back. */
            if (++isInT[s[head++] - 'A'] > 0)   n++;
        }
    }
    if (res_length == INT_MAX)  return "";
    res = (char *)malloc((res_length + 1) * sizeof(char));
    if (!res) {
        perror("Error");
        return NULL;
    }
    strncpy(res, s + from, res_length);
    res[res_length] = '\0';
    return res;
}

int main()
{
    char *s = "ADOBECODEBANC", *t = "ABC";
    printf("%s", minWindow(s, t));
    return 0;
}
