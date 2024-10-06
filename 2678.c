#include <stdio.h>

int countSeniors(char **, int);

int countSeniors(char **details, int detailsSize)
{
    int res = 0;
    for (int i = 0; i < detailsSize; i++)
        res += ((details[i][11] > '6') || ((details[i][11] == '6') && (details[i][12] > '0')));
    return res;
}

int main()
{
    char *details[] = {"7868190130M7522", "5303914400F9211", "9273338290F4010"};
    printf("%d\n", countSeniors(details, 3));
    return 0;
}
