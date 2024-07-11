#include <stdio.h>
#include <string.h>

int minOperations(char **logs, int logsSize)
{
    int res = 0;
    for (int i = 0; i < logsSize; i++)
        if (!strcmp(logs[i], "../"))
            res -= !!res;
        else
            res += !!strcmp(logs[i], "./");
    return res;
}

int main()
{
    char *logs[] = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
    printf("%d\n", minOperations(logs, 6));
    return 0;
}
