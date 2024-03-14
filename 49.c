#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_MAGNITUDE 5 /* There will be at most 10^5 strings. */

int true_strlen(char *s);
int cmpstr(const void *a, const void *b);
int cmpchar(const void *a, const void *b);
char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes);

int true_strlen(char *s)
{
    /* Including '\0' */
    return 1 + strlen(s);
}

/* A cmp function in order to make strncmp() as a qsort() argument */
int cmpstr(const void * a, const void * b)
{
    /**
     * Inputs need to be the pointers of strings i.e. char **.
     * strncmp() with the length of the longer one
     */
    return strncmp(*(char const **)a, *(char const **)b, (strlen(*(char const **)a) > strlen(*(char const **)b) ? strlen(*(char const **)a) : strlen(*(char const **)b)));
}

int cmpchar(const void *a, const void *b)
{
    /**
     * Sort input strings.
     * e.g. "cab" => "abc"
     * Inputs need to be treated as char * rather than int *, or it may not be sorted normally.
     */
    return ( *(char *)a - *(char *)b );
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
{
    char ***res;
    *returnSize = 1;
    if (strsSize == 1) {
        int s = true_strlen(*strs);
        /* Just return strs as a group */
        **returnColumnSizes = 1;
        res = (char ***)malloc(sizeof(char **));
        *res = (char **)malloc(sizeof(char *));
        **res = (char *)malloc(s * sizeof(char));
        strncpy(**res, *strs, s);
    }
    else {
        /* For the sorted string */
        char **qstrs = (char **)malloc(strsSize * sizeof(char *));
        char str[MAX_LENGTH_MAGNITUDE];
        int j = 0, k = 0, * indices = (int *)malloc(strsSize * sizeof(int));
        char * a, * b;
        for (int i = 0; i < strsSize; i++) {
            qstrs[i] = (char *)malloc((true_strlen(strs[i]) + MAX_LENGTH_MAGNITUDE) * sizeof(char));
            strncpy(qstrs[i], strs[i], true_strlen(strs[i]));
            if (!qstrs[i][0])
                /**
                 * Some errors will be caused during the following sections (strtok()) by the empty string.
                 * Thus, a char '@' that will never exist in the original input will be inserted.
                 * Also, there is no need to sort an empty string.
                 */
                strncpy(qstrs[i], "@", 2);
            else if (strlen(qstrs[i]) > 1)
                /**
                 * If the input isn't a empty string nor a single character,
                 * it gets sorted here.
                 * Thus, all anagrams that belong to a same group will be the same.
                 * e.g. {"ate", "eat", "tea"} => {"aet", "aet", "aet"}
                 */
                qsort(qstrs[i], strlen(qstrs[i]), sizeof(qstrs[i][0]), cmpchar);
            /**
             * Original indices are needed in order to restore them back after input strings get grouped.
             * Thus, each of them get stored as a suffix following the sorted string 
             * instead of getting stored like a struct.
             * A char '~' that will never exist in the original input strings is used here making the suffix distinguishable.
             * e.g. qstrs[1] = "cab" => qstrs[1] = "abc~1"
             * str[5] is used here for the converted index from int to string,
             * so the number '5' is taken because the length is < 10^5.
             */
            sprintf(str, "%d", i);
            strncat(qstrs[i], "~", 2);
            strncat(qstrs[i], str, strlen(str));
        }
        /**
         * Sort the whole qstrs.
         * Since all anagrams are same here, they will be gathered together.
         */
        qsort(qstrs, strsSize, sizeof(char *), cmpstr);
        /* Get the anagram */
        a = strtok(qstrs[0], "~");
        /* Get its index */
        sscanf(strtok(NULL, "~"), "%d", &(indices[0]));
        for (int i = 1; i < strsSize; i++) {
            b = strtok(qstrs[i], "~");
            sscanf(strtok(NULL, "~"), "%d", &(indices[i]));
            if (strncmp(a, b, strlen(a)))
                /**
                 * If there are two different anagrams, there are at least 2 groups.
                 * Since *returnSize is initially being 1, *returnSize++.
                 */
                (*returnSize)++;
            /* Iterate */
            a = b;
        }
        /* Now the sorted indices and the number of groups are obtained, the only thing left is grouping. */
        *returnColumnSizes = (int *)malloc((*returnSize) * sizeof(int *));
        for (int i = 1, h = 0; i < strsSize; i++) {
            if (strncmp(qstrs[h], qstrs[i], strlen(qstrs[h]))) {
                /**
                 * If there are two different anagrams, the former one is the end of a group,
                 * so the new group is between it and the recorded position for the last time.
                 */
                (*returnColumnSizes)[j++] = i - k;
                /* Update the recorded position */
                k = i;
            }
            h++;
        }
        /* The last group aren't recorded before the loop broke */
        (*returnColumnSizes)[j] = strsSize - k;
        res = (char ***)malloc((*returnSize) * sizeof(char **));
        for (int i = 0; i < *returnSize; i++)
            res[i] = (char **)malloc((*returnColumnSizes)[i] * sizeof(char *));
        for (int i = 0, * iter = indices; i < *returnSize; i++)
            for (int l = 0, s = 0; l < (*returnColumnSizes)[i]; l++) {
                s = true_strlen(strs[*iter]);
                res[i][l] = (char *)malloc(s * sizeof(char));
                /**
                 * Since the indices are sorted, 
                 * the output gets its content directly from them while grouping by the recorded group sizes.
                 */
                strncpy(res[i][l], strs[*iter], s);
                iter++;
            }
        for (int i = 0; i < strsSize; i++)
            free(qstrs[i]);
        free(qstrs);
        free(indices);
    }
    return res;
}

int main()
{
    int strsSize = 6, returnSize, *returnColumnSizes;
    char **strs = (char **)malloc(strsSize * sizeof(char *)), ***res;
    strs[0] = "eat";
    strs[1] = "tea";
    strs[2] = "tan";
    strs[3] = "ate";
    strs[4] = "nat";
    strs[5] = "bat";
    res = groupAnagrams(strs, strsSize, &returnSize, &returnColumnSizes);
    printf("[");
    for (int i = 0; i < returnSize; i++)
    {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++)
        {
            printf("\"%s\"", res[i][j]);
            if (j + 1 < returnColumnSizes[i])   printf(",");
            free(res[i][j]);
        }
        printf("]");
        free(res[i]);
        if (i + 1 < returnSize)   printf(",");
    }
    printf("]");
    free(strs);
    free(returnColumnSizes);
    free(res);
    return 0;
}
