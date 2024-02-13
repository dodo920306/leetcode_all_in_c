#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/* The number of characters including uppercase and lowercase English letters and digits */
#define NUMBER_OF_VALID_ASCII 75

/* A struct to record index (key) after being sorted */
struct pair {
    char key;
    int freq;
};

int cmp(const void * a, const void * b)
{
    /* Sort in decreasing order based on the frequency of the characters */
    return ( (*(struct pair *)b).freq - (*(struct pair *)a).freq );
}

char* frequencySort(char* s)
{
    int length = strlen(s);
    struct pair f[NUMBER_OF_VALID_ASCII];

    for (int i = 0; i < NUMBER_OF_VALID_ASCII; i++)
    {
        /* Initialize */
        f[i].key = i + '0';
        f[i].freq = 0;
    }
    for (int i = 0; i < length; i++)
    {
        /* Calculate the frequency of each character in the input string */
        f[s[i] - '0'].freq++;
    }

    qsort(f, NUMBER_OF_VALID_ASCII, sizeof(struct pair), cmp);

    for (int i = 0, j = 0; j < length; i++)
    {
        while (f[i].freq--) {
            s[j++] = f[i].key;
        }
    }
    return s;
}

int main()
{
    char s[4] = "tree";
    char *res = frequencySort(s);
    for (int i = 0; i < 4; i++)
    {
        printf("%c", res[i]);
    }
    free(res);
    return 0;
}
