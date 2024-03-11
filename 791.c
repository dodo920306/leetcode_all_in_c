#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ordering {
    int index, order, count;
};

int cmp(const void *a, const void *b);
char *customSortString(char *order, char *s);

int cmp(const void *a, const void *b)
{
    return ((struct ordering *)a)->order - ((struct ordering *)b)->order;
}

char *customSortString(char *order, char *s)
{
    int order_length = strlen(order), s_length = strlen(s);
    struct ordering map[26];

    for (int i = 0; i < 26; i++) {
        map[i].index = i + 'a';
        map[i].order = INT_MAX;
        map[i].count = 0;
    }

    for (int i = 0; i < order_length; i++)
        map[order[i] - 'a'].order = i;

    for (int i = 0; i < s_length; i++)
        map[s[i] - 'a'].count++;

    qsort(map, 26, sizeof(struct ordering), cmp);
    for (int i = 0, j = 0; i < 26; i++)
        while (map[i].count--) s[j++] = map[i].index;

    return s;
}

int main()
{
    char s[] = "abcd";
    printf("%s", customSortString("bcafg", s));
    return 0;
}
