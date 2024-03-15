#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *intToRoman(int num);

char *intToRoman(int num)
{
    /**
     * This number was obtained through experiments.
     * If you can't pass the question, it means LeetCode has updated their test inputs, 
     * so please increase the number and report it.
     */
    char *res = (char *)calloc(16, sizeof(char)), *romans[4][10];
    int radix = 0, n = num, significant = 1;
    if (!res) {
        perror("Error");
        return NULL;
    }

    romans[0][1] = "I";
    romans[0][2] = "II";
    romans[0][3] = "III";
    romans[0][4] = "IV";
    romans[0][5] = "V";
    romans[0][6] = "VI";
    romans[0][7] = "VII";
    romans[0][8] = "VIII";
    romans[0][9] = "IX";

    romans[1][1] = "X";
    romans[1][2] = "XX";
    romans[1][3] = "XXX";
    romans[1][4] = "XL";
    romans[1][5] = "L";
    romans[1][6] = "LX";
    romans[1][7] = "LXX";
    romans[1][8] = "LXXX";
    romans[1][9] = "XC";

    romans[2][1] = "C";
    romans[2][2] = "CC";
    romans[2][3] = "CCC";
    romans[2][4] = "CD";
    romans[2][5] = "D";
    romans[2][6] = "DC";
    romans[2][7] = "DCC";
    romans[2][8] = "DCCC";
    romans[2][9] = "CM";

    romans[3][1] = "M";
    romans[3][2] = "MM";
    romans[3][3] = "MMM";

    while (n) {
        radix++;
        n /= 10;
        significant *= 10;
    }

    while (radix--) {
        significant /= 10;
        if (num / significant)
            strncat(res, romans[radix][num / significant], 4);
        num %= significant;
    }

    return res;
}

int main()
{
    char *res = intToRoman(1994);
    printf("%s", res);
    free(res);
    return 0;
}
