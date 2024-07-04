#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Queue {
    int start;
    int end;
    int array[10000];
};

bool isEmpty(struct Queue *q);
void push(struct Queue *q, int k);
void pop(struct Queue *q);
int peek(struct Queue *q);
char *predictPartyVictory(char *senate);

bool isEmpty(struct Queue *q)
{
    return q->start >= q->end;
}

void push(struct Queue *q, int k)
{
    q->array[q->end++] = k;
}

void pop(struct Queue *q)
{
    q->start++;
}

int peek(struct Queue *q)
{
    return q->array[q->start];
}

char *predictPartyVictory(char *senate)
{
    struct Queue *r, *d;
    int length = strlen(senate);
    bool res;

    if (!(r = (struct Queue *)calloc(1, sizeof(struct Queue))) || !(d = (struct Queue *)calloc(1, sizeof(struct Queue))))
        return NULL;
    for (int i = 0; i < length; i++)
        if (senate[i] == 'R')   push(r, i);
        else    push(d, i);
    while (!isEmpty(r) && !isEmpty(d)) {
        /**
         * compare the head of each queue and push the winner back to its queue
         *
         * Pushing the winner back means it stays to the next round,
         * so that it won't ban others and still can be banned.
         *
         * For example, the input is "DRRDRDRDRDDRDRDR".
         *
         * First we get a D to ban an R,
         * so we get "DRDRDRDRDDRDRDR".
         *
         * Next we get an R to ban a D.
         * If the first D now still stays as the head of the D queue,
         * it can still ban this R before it can do anything.
         * Thus, iterations are stuck.
         *
         * Finally, an R is the last one to take actions in the queue.
         * The best choice for it to do is ban a D before it.
         * If these Ds weren't pushed again, this R can't achieve it.
         *
         * What if we use an index to iterate queues and allow only when
         * peek(q) == i can actions be taken?
         * This will solve the both problems since it can ban others with smaller indices
         * while keep iterations going.
         * However, if we keep the winner banning from the head of the queue,
         * it sometimes won't do the best choice,
         * Still, we take "DRRDRDRDRDDRDRDR" for example.
         * After the first D bans the next R,
         * the first R is popped, and the next R can take actions.
         * The best choice it should do is ban the second D on the fourth position
         * since it still can ban a R in this round next, so doing so can save an R.
         * However, if we keep the winner to ban others with smaller indices, this R
         * will ban the first D since it hasn't be banned (popped).
         * In the end, we will waste an R in this round.
         *
         * In conclusion, both the winner and the loser have to be popped, 
         * but the winner can be pushed back again.
         */
        if (peek(r) < peek(d))
            push(r, length++);
        else
            push(d, length++);
        pop(r);
        pop(d);
    }
    res = isEmpty(d);
    free(r);
    free(d);
    return res ? "Radiant" : "Dire";
}

int main()
{
    printf("%s\n", predictPartyVictory("DRRDRDRDRDDRDRDR"));
    return 0;
}
