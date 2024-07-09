#include <stdio.h>

double averageWaitingTime(int **customers, int customersSize, int *customersColSize);

double averageWaitingTime(int **customers, int customersSize, int *customersColSize)
{
    double sum = 0;

    for (int i = 0, time = 0; i < customersSize; i++) {
        if (time < customers[i][0])
            time = customers[i][0];
        time += customers[i][1];
        sum += time - customers[i][0];
    }
    return sum / customersSize;
}

int main()
{
    int customer1[] = {5, 2}, customer2[] = {5, 4}, customer3[] = {10, 3}, customer4[] = {20, 1}, *customers[] = {customer1, customer2, customer3, customer4}, customersColSize[] = {2, 2, 2, 2};
    printf("%lf\n", averageWaitingTime(customers, 4, customersColSize));
    return 0;
}
