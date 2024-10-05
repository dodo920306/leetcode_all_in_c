#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b);
long long dividePlayers(int *skill, int skillSize);

int cmp(const void *a, const void *b)
{
    return (*(int *)a) - (*(int *)b);
}

long long dividePlayers(int *skill, int skillSize)
{
    long long res = 0;
    int _skill = 0;
    if (skillSize == 2) return skill[0] * skill[1];

    qsort(skill, skillSize, sizeof(int), cmp);

    skillSize--;
    res = skill[0] * skill[skillSize];
    _skill = skill[0] + skill[skillSize];
    skillSize--;
    for (int i = 1, j = skillSize; i < j; j--) {
        if (skill[i] + skill[j] != _skill)  return -1;
        res += skill[i] * skill[j];
        i++;
    }
    return res;
}

int main()
{
    int skills[] = {3, 2, 5, 1, 3, 4};
    printf("%lld\n", dividePlayers(skills, 6));
    return 0;
}
