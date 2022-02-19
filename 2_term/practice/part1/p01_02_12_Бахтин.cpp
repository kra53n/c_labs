#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "popular_func.h"

/* Название файла с заданием: 02_praktika_05.02.2022
 * Задание:
 * Дан массив. Переписать его элементы в другой массив такого же размера
 * следующим образом: сначала должны идти все отрицательные элементы, а затем
 * все остальные. Использовать тольно один проход по исходному массиву.
*/

int main()
{
    int arrSize = scanArrSize(1, 20);
    int arr1[20], arr2[20], arrPositive[20], arrNegative[20];
    int arrNegativeSize = 0, arrPositiveSize = 0;
    srand(time(0));

    fillArrRandomly(arr1, arrSize, -20, 20);
    printf("\nСгенерированный массив из %d элементов:\n", arrSize);
    printArr(arr1, arrSize, 1);

    for (int i = 0; i < arrSize; i++)
    {
        if (arr1[i] < 0)
        {
            arrNegative[arrNegativeSize] = arr1[i];
            arrNegativeSize++;
        }
        else
        {
            arrPositive[arrPositiveSize] = arr1[i];
            arrPositiveSize++;
        }
    }

    int i = 0;
    for (int j = 0; j < arrNegativeSize; j++, i++)
        arr2[i] = arrNegative[j];
    for (int j = 0; j < arrPositiveSize; j++, i++)
        arr2[i] = arrPositive[j];

    printf("\nПолучаемый массив:\n");
    printArr(arr2, arrSize, 1);

    return 0;
}
