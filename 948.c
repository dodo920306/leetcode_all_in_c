#include <stdio.h>
#include <stdlib.h>

void countingsort(int *nums, int numsSize)
{
    if (numsSize <= 1)  return;
    int *freq = (int *)calloc(10000, sizeof(int));
    if (!freq) {
        perror("Error");
        return;
    }
    for (int i = 0; i < numsSize; i++) freq[nums[i]]++;
    for (int i = 0, j = 0; i < numsSize; j++)
        while (freq[j]--)   nums[i++] = j;
    free(freq);
}

int bagOfTokensScore(int *tokens, int tokensSize, int power)
{

    int score = 0, res = 0;
    countingsort(tokens, tokensSize);

    for (int i = 0, j = tokensSize - 1; i <= j;) {
        /* check a token per loop in case of the index overflow */
        if (power >= tokens[i]) {
            power -= tokens[i++];
            score++;
            if (score > res)    res = score;
        }
        /**
         * check a token per loop in case that we turn every of the rest of them
         * while some of them can be played in the next loop to 
         * increase our score
         */
        else if (score) {
            power += tokens[j--];
            score--;
        }
        /* check if there is change to prevent the infinite loop */
        else    break;
    }
    return res;
}

int main()
{
    int tokens[] = {100, 200, 300, 400};
    printf("%d", bagOfTokensScore(tokens, 4, 200));
    return 0;
}
