#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char* generateString(char* str1, char* str2);

int main() {
    char* res1 = generateString("TFTF", "ab");
    printf("%s\n", res1);
    free(res1);

    char* res2 = generateString("TFTF", "abc");
    printf("%s\n", res2);

    char* res3 = generateString("F", "d");
    printf("%s\n", res3);
    free(res3);
    return 0;
}

char* generateString(char* str1, char* str2) {
    int n = strlen(str1);
    int m = strlen(str2);
    int resLength = n + m - 1;

    bool fixed[resLength];
    char* res = (char*)malloc((resLength + 1) * sizeof(char));
    for (int i = 0; i < resLength; i++) {
        /* Set the result all to 'a' */
        res[i] = 'a';
        fixed[i] = false;
    }
    res[resLength] = '\0';

    for (int i = 0; i < n; i++) {
        if (str1[i] == 'F') {
            continue;
        }

        for (int j = 0; j < m; j++) {
            if (!fixed[i + j]) {
                res[i + j] = str2[j];
                fixed[i + j] = true;
            } else if (res[i + j] != str2[j]) {
                free(res);
                return "";
            }
        }
    }


    for (int i = 0; i < n; i++) {
        if (str1[i] == 'T') {
            continue;
        }

        bool isSubstringAlreadyDifferent = false;
        for (int j = 0; j < m; j++) {
            if (res[i + j] != str2[j]) {
                isSubstringAlreadyDifferent = true;
                break;
            }
        }
        if (isSubstringAlreadyDifferent) {
            /* The substring is already different */
            continue;
        }

        /* The substring is same as str2 */
        for (int j = m - 1; j >= 0; j--) {
            if (!fixed[i + j]) {
                /* The unfixed characters must be 'a'
                 * becaused they haven't been changed.
                 *
                 * Since the substring is still same as str2,
                 * we can say str2[j] = res[i + j] = 'a'.
                 * 
                 * Thus, if res[i + j] = 'b' != str2, we can
                 * say the substring is different while keeping
                 * it sexicographically smallest because j is
                 * the rightest unfixed character index.
                 */
                res[i + j] = 'b';
                isSubstringAlreadyDifferent = true;
                break;
            }
        }
        /* The substring is still the same
         * => all characters here are fixed 
         * => return
         */
        if (!isSubstringAlreadyDifferent) {
            free(res);
            return "";
        }
    }
    return res;
}
