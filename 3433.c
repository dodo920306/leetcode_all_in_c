#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b);
int* countMentions(int numberOfUsers, char*** events, int eventsSize, int* eventsColSize, int* returnSize);

int main()
{
    /**
     * We will use strtok() later on the third element,
     * so it must be editable since strtok will insert
     * '\0's in the string.
     * Thus, we use strdup() here to ensure that it's
     * not a string constant that is read only.
     */
    char* event1[] = {"MESSAGE", "10", strdup("id1 id0")};
    char* event2[] = {"OFFLINE","11","0"};
    char* event3[] = {"MESSAGE","71","HERE"};
    char** events[] = {event1, event2, event3};
    int eventsColSize[] = {3, 3, 3};
    int returnSize = 0;
    int* res = countMentions(2, events, 3, eventsColSize, &returnSize);
    printf("[");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", res[i]);
        if (i + 1 != returnSize) {
            printf(", ");
        }
    }
    printf("]\n");
    free(res);
    return 0;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countMentions(int numberOfUsers, char*** events, int eventsSize, int* eventsColSize, int* returnSize)
{
    int *offlineTimestamps = calloc(numberOfUsers, sizeof(int));
    int *res = calloc(numberOfUsers, sizeof(int));
    qsort(events, eventsSize, sizeof(char **), cmp);
    for (int i = 0; i < eventsSize; i++) {
        if (!strcmp("OFFLINE", events[i][0])) {
            offlineTimestamps[atoi(events[i][2])] = atoi(events[i][1]) + 60;
            continue;
        }
        if (!strcmp("HERE", events[i][2])) {
            for (int j = 0; j < numberOfUsers; j++) {
                if (atoi(events[i][1]) >= offlineTimestamps[j]) {
                    res[j]++;
                }
            }
            continue;
        }
        if (!strcmp("ALL", events[i][2])) {
            for (int j = 0; j < numberOfUsers; j++) {
                res[j]++;
            }
            continue;
        }
        char *id = strtok(events[i][2], " ");
        while (id) {
            res[atoi(id + 2)]++;
            id = strtok(NULL, " ");
        }
    }
    free(offlineTimestamps);
    *returnSize = numberOfUsers;
    return res;
}

int cmp(const void *a, const void *b)
{
    char **eventA = *(char ***)a;
    char **eventB = *(char ***)b;
    int timestampCmp = atoi(eventA[1]) - atoi(eventB[1]);
    return timestampCmp ? timestampCmp : strcmp(eventB[0], eventA[0]);
}
