#include <stdio.h>
#include <stdbool.h>

bool isPowerOfTwo(int n);

bool isPowerOfTwo(int n)
{
    /* return n && (!(n >> ((sizeof(int) * CHAR_BIT) - 1))) && (!(n & (n - 1))); */
    return (n > 0) && (!(n & (n - 1)));
}

int main()
{
    printf("%s", isPowerOfTwo(16) ? "true" : "false");
    return 0;
}
