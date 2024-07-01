#include <stdio.h>
#include <string.h>

int compress(char *chars, int charsSize);

int compress(char *chars, int charsSize)
{
    char buffer[5];
    int i = 0, j = 1, length = 0;
    /* check if j is in either old or new string end */
    for (int k = 0; j < charsSize && chars[j] != '\0'; j++)
        if (chars[i] != chars[j]) {
            /* check if this is a consecutive group of characters */
            if (j - i > 1) {
                /**
                 * get the length of number in string
                 *
                 * Directly sprintf() into the input string may
                 * overwrite the content next or 
                 * overflow the heap buffer with the trailing '\0', 
                 * so use a buffer first.
                 */
                length = sprintf(buffer, "%hd", j - i);
                /**
                 * The first latter has to be reserved, so
                 * i is moved right for 1 step.
                 */
                i++;
                /* paste the buffer with limited length to get rid of the trailing '\0' */
                strncpy(chars + i, buffer, length);
                /**
                 * Move i to where the number string ends, 
                 * which should be the beginning of the next group.
                 */
                i += length;
                /* Some space is remained between i and j. */
                if (i != j) {
                    /* find the new string end */
                    k = i;
                    for (int l = j; l < charsSize && chars[l] != '\0'; l++)
                        chars[k++] = chars[l];
                    /* make k the new end of the string */
                    chars[k] = '\0';
                    /* adjust j to the beginning of the next group */
                    j = i;
                }
            }
            else
                /* omit */
                i = j;
        }
    if (j - i > 1) {
        length = sprintf(buffer, "%hd", j - i);
        i++;
        strncpy(chars + i, buffer, length);
        return i + length;
    }
    /* add 1 for length representation */
    return i + 1;
}

int main()
{
    char chars[] = {'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'};
    int res = compress(chars, 13);
    for (int i = 0; i < res; i++)   printf("%c", chars[i]);
    printf("\n");
    return 0;
}
