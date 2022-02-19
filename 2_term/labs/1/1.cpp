#include <stdio.h>

/* Задание:
 * Вычислить сумму и произведение всех чисел от А до В.
 * */

void askUserIntervals(int *start, int *end)
{
    int cond;
    do {
        printf("Выберите [A;B]:\n");
        printf("[A]: "); scanf("%d", start);
        printf("[B]: "); scanf("%d", end);

        cond = *start > *end;
        if (cond)
            printf("Были введены неверные концы интервала, А <= B! Попробуйте снова!");

    } while(cond);
}

int intervalSum(int start, int end)
{
    int sum = 0;
    for (int i = start; i <= end; i++)
        sum += i;
    return sum;
}

int intervalProduct(int start, int end)
{
    int product = 1;
    for (int i = start; i <= end; i++)
        product *= i;
    return product;
}

int main()
{
    int start, end;
    int *start_ptr = &start, *end_ptr = &end;

    askUserIntervals(start_ptr, end_ptr);
    printf("\nСумма чисел: %d\n", intervalSum(start, end));
    printf("Произведение чисел: %d", intervalProduct(start, end));

    return 0;
}
