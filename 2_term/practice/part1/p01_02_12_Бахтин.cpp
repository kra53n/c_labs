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
    int arr1[20], arr2[20];

    srand(time(0));
    fillArrRandomly(arr1, arrSize, -20, 20);
    printf("\nСгенерированный массив из %d элементов:\n", arrSize);
    printArr(arr1, arrSize, 1);

    for (int go = 0, i = 0, j = arrSize - 1; go < arrSize; go++)
    {
        int elem = arr1[go];
        if (elem < 0)
        {
            arr2[i++] = elem;
            continue;
        }
        arr2[j--] = elem;
    }

    printf("\nПолучаемый массив:\n");
    printArr(arr2, arrSize, 1);

    return 0;
}
