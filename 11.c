#include <stdio.h>
#include <limits.h>

int maxArea(int *height, int heightSize);

int maxArea(int *height, int heightSize)
{
    int i = 0, j = heightSize - 1, res = INT_MIN, area = 0;
    while (i < j) {
        if (height[i] < height[j]) {
            area = height[i] * (j - i);
            i++;
        }
        else {
            area = height[j] * (j - i);
            j--;
        }
        if (res < area)  res = area;
    }
    return res;
}

int main()
{
    int height[] = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    printf("%d\n", maxArea(height, 9));
    return 0;
}
