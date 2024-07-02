#include <stdio.h>
#include <stdlib.h>

int largestAltitude(int *gain, int gainSize);

int largestAltitude(int *gain, int gainSize)
{
    int res = 0, *altitude;
    gainSize++;
    if (!(altitude = (int *)malloc(gainSize * sizeof(int))))
        return -1;
    altitude[0] = 0;
    for (int i = 1; i < gainSize; i++) {
        altitude[i] = altitude[i - 1] + gain[i - 1];
        if (res < altitude[i])
            res = altitude[i];
    }
    free(altitude);
    return res;
}

int main()
{
    int gain[] = {-5, 1, 5, 0, -7};
    printf("%d\n", largestAltitude(gain, 5));
    return 0;
}
