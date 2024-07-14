#include <stdio.h>
#include <string.h>

#define SWAP(x, y)          \
do {                        \
  __typeof__(x) tmp = (x);  \
  (x) = (y);                \
  (y) = tmp;                \
} while (0)

void reverseString(char *s);
int maximumGain(char *s, int x, int y);

void reverseString(char *s)
{
    int i = 0, j = strlen(s) - 1;
    while (i < j) {
        SWAP(s[i], s[j]);
        i++;
        j--;
    }
}

int maximumGain(char *s, int x, int y)
{
    int a = 0, b = 0, res = 0;
    if (x < y) {
        /* If ba is more profitable than ab, swap them and the whole string. */
        SWAP(x, y);
        reverseString(s);
    }
    for (int i = 0, length = strlen(s); i < length; i++) {
        /**
         * If there is an ab, remove it by decreasing a and not increasing b.
         * An ab is determined by the order.
         * If a b is encountered after a, an ab is encountered.
         * Since there won't be an ab or ba being formed across 2 groups of 'a's and 'b's,
         * once a letter which isn't a or b is encountered,
         * a and b will be reset.
         * Meanwhile, if a and b isn't 0,
         * there must be some ba since all 'ab's are removed during the iterations.
         * The number of ba will the minimum of a and b.
         * Why remove ab before ba?
         * Because ab must be more profitable than ba.
         * Why remove more profitable ones than the other will give us the maximum score?
         * Assume there exists an optimal sequence where removing 'ba' is more optimal than removing 'ab'.
         * Since x >= y, This would imply removing 1 'ab' restricts us from removing 2 'ba's or more,
         * i.e., every 'ab' is shared by 2 'ba's.
         * Consider the string 'baba'.
         * If we remove 'ba' first, we are left with another 'ba', totaling 2y points.
         * Conversely, if we remove 'ab' first, we are left with one 'ba',
         * totaling x + y points.
         * Since x >= y, 2y <= x + y.
         * Thus, our initial assumption is wrong.
         * There doesn't exist an optimal sequence where removing 'ba' is more optimal than removing 'ab'.
         */
        if (s[i] == 'a')    a++;
        else if (s[i] == 'b')
            if (a) {
                /* There's ab */
                a--;
                res += x;
            }
            else
                b++;
        else {
            /* There's ba */
            res += y * (b < a ? b : a);
            a = b = 0;
        }
    }
    /* There's ba */
    return res + y * (b < a ? b : a);
}

int main()
{
    char s[] = "cdbcbbaaabab";
    printf("%d\n", maximumGain(s, 4, 5));
    return 0;
}
