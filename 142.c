#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *detectCycle(struct ListNode *head);

struct ListNode *detectCycle(struct ListNode *head)
{
    if (!head || !(head->next)) return NULL;
    struct ListNode *slow = head->next, *fast = head->next->next;
    while (fast != slow) {
        if (!fast || !(fast->next))  return NULL;
        slow = slow->next;
        fast = fast->next->next;
    }
    /**
     * At this moment, f = 2s, and f = d(head, tail->next) + n * cycle + d(tail->next, meet_point).
     * s = d(head, tail->next) + m * cycle + d(tail->next, meet_point).
     * Thus, d(head, tail->next) + n * cycle + d(tail->next, meet_point)
     *     = 2 * d(head, tail->next) + 2 * m * cycle + 2 * d(tail->next, meet_point)
     *    => d(head, tail->next) = (n - 2 * m) * cycle - d(tail->next, meet_point)
     *       (d(tail->next, meet_point) = cycle - d(meet_point, tail->next))
     *    => d(head, tail->next) = (n - 2 * m - 1) * cycle + d(meet_point, tail->next)
     * Therefore, if (n - 2 * m - 1) >= 0,
     * two pointer start from the head and the meetup node respectively moving at the same speed 
     * will finally meet each other at tail->next.
     * 
     * Let us say that when the slow one enter the cycle i.e. it's on the tail->next,
     * d(fast, tail->next) = k < cycle.
     * Thus, d(fast, slow) = k at the forward direction.
     * Since the fast pointer moves one step more than the slow one,
     * d(fast, slow)-- for every step, and they meet up only when d(fast, slow) = 0.
     * In other word, the slow one will only move k steps before it meets with the fast one.
     * Thus, since k < cycle, m = 0, so (n - 2 * m - 1) >= 0 => n >= 1.
     * 
     * Moreover, by the derivation above, and trivially the slow pointer will never catch up the fast one,
     * the fast one has to catch up the slow one itself.
     * Thus, in addition to what the fast pointer has moved in the cycle before the slow one entered,
     * the fast pointer must move for at least one cycle.
     * So, n >= 1, trivially.
     * In conclusion,
     * two pointer start from the head and the meetup node respectively moving at the same speed
     * must meet each other at tail->next.
     */
    fast = head;
    while (fast != slow) {
        fast = fast->next;
        slow = slow->next;
    }
    return fast;
}

int main()
{
    struct ListNode node4 = {.val = -4, .next = NULL}, node3 = {.val = 0, .next = &node4}, node2 = {.val = 2, .next = &node3}, head = {.val = 3, .next = &node2};
    node4.next = &node2;

    printf("%d\n", detectCycle(&head)->val);
    return 0;
}
