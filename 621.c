#include <stdio.h>

int leastInterval(char *tasks, int tasksSize, int n);

int leastInterval(char *tasks, int tasksSize, int n)
{
    int freq[26] = {0}, max = 0, res;

    for (int i = 0; i < tasksSize; i++) {
        freq[tasks[i] - 'A']++;
        if (freq[tasks[i] - 'A'] > max) max = freq[tasks[i] - 'A'];
    }

    /**
     * The whole amount of time doing tasks will be at least 
     * the length of a interval (n + 1) multiplying the maximum number of intervals for each task (max - 1).
     */
    res = (max - 1) * (n + 1);
    /**
     * If there are many tasks with same number of intervals as the maximum,
     * the result will increase because all of these kind of tasks needs this many of intervals.
     */
    for (int i = 0; i < 26; i++)    if (freq[i] == max) res++;
    /**
     * If there are too many tasks having less than maximum intervals, 
     * they may not be able to fit in the intervals between tasks with maximum intervals,
     * so the amount of all tasks may be larger than the original result.
     * In this case, after all tasks with maximum intervals have been finished, 
     * there are still tasks left to do.
     * Otherwise, all tasks can fit in, or there is some idle time.
     */
    return res > tasksSize ? res : tasksSize;
}

int main()
{
    char tasks[] = {'A', 'C', 'A', 'B', 'D', 'B'};
    printf("%d\n", leastInterval(tasks, 6, 1));
    return 0;
}
