#include <stdio.h>
#include "popular_func.h"

/* Название файла с заданием: 02_praktika_05.02.2022
 * Задание:
 * Дан одномерный массив. Переставить в обратном порядке:
 *   а) элементы, расположенные между вторым и десятым элменетами
 *   б) элементы, расположенные между k-м и s-м элементами при k < s
 *   в) элементы, расположенные между максимальным и минимальным элементами,
 *   включая их
*/

void reverseOrderInArr(double arr[], int arrSize, int beginInd, int endInd)
{
    double tmp;
    for (int i = beginInd, j = endInd; i < j; i++, j--)
    {
        tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}

int main()
{
    int arrSize = 15;
    double arr[15];

    printf("\nВведите массив из %d элементов:\n", arrSize);
    scanArrManuallyF(arr, arrSize, 1);

    reverseOrderInArr(arr, arrSize, 2, 8);
    printf("\n");
    printArrF(arr, arrSize, 1);

    int k, s;
    printf("\nВведите диапозон (k;s), для изменения порядка элементов массива:");
    do {
        printf("\nВведите k: "); scanf("%d", &k);
        printf("Введите s: "); scanf("%d", &s);
        if (k >= s || k < 1 || s > arrSize)
            printf("\nПроверте соблюдение: k < s; k >= 1; s <= 15; k, s - целые числа.");
    } while (k >= s || k < 1 || s > arrSize);
    printf("\nМассив, элементы которого перевёрнуты в промежутке от k до s:\n");
    reverseOrderInArr(arr, arrSize, k, s - 2);
    printArrF(arr, arrSize, 1);


    printf("\nМассив, элементы которого перевёрнуты в отрезке от индексов минимального и максимального значений:\n");
    int min = minIndF(arr, arrSize);
    int max = maxIndF(arr, arrSize);
    reverseOrderInArr(arr, arrSize, min, max);
    printArrF(arr, arrSize, 1);

    return 0;
}
