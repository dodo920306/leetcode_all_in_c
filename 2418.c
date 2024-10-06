#include <stdio.h>
#include <stdlib.h>

struct person {
    char *name;
    int height;
};

int cmp(const void *a, const void *b);
char **sortPeople(char **names, int namesSize, int *heights, int heightsSize, int *returnSize);
void printStrArray(char **, int);

int cmp(const void *a, const void *b)
{
    return ((struct person *)b)->height - ((struct person *)a)->height;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char **sortPeople(char **names, int namesSize, int *heights, int heightsSize, int *returnSize)
{
    struct person *people = (struct person *)malloc(namesSize * sizeof(struct person));
    *returnSize = 0;
    if (!people) {
        fprintf(stderr, "Error: Memory Allocation Failed.");
        return NULL;
    }

    for (int i = 0; i < namesSize; i++) {
        people[i].name = names[i];
        people[i].height = heights[i];
    }
    qsort(people, namesSize, sizeof(struct person), cmp);
    for (int i = 0; i < namesSize; i++)
        names[i] = people[i].name;

    *returnSize = namesSize;
    free(people);
    return names;
}

void printStrArray(char **arr, int arrSize)
{
    arrSize--;
    printf("[");
    for (int i = 0; i < arrSize; i++) {
        printf("%s, ", arr[i]);
    }
    if (arrSize >= 0)
        printf("%s]\n", arr[arrSize]);
    else
        printf("]\n");
}

int main()
{
    int heights[] = {180, 165, 170}, returnSize = 0;
    char **names = (char **)malloc(3 * sizeof(char *)), \
         **res = NULL;
    names[0] = "Mary";
    names[1] = "John";
    names[2] = "Emma";
    res = sortPeople(names, 3, heights, 3, &returnSize);
    printStrArray(res, returnSize);
    free(res);
    return 0;
}
