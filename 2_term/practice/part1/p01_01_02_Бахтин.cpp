#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "popular_func.h"

/* Название файла с заданием: 01_praktika_05.02.2022
 * Задание:
 * Дан массив вещественных сулчайных чисел (размер массива определяет
 * пользователь в диапозоне [3;20]). Найти минимальне число.
*/

void fillArrRandomly(double arr[],  int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = (rand() * rand()) / 1000.;
}

int main()
{
    int arrMinSize = 3, arrMaxSize = 20, arrSize;
    double arr[20];

    srand(time(0));
    arrSize =  scanArrSize(arrMinSize, arrMaxSize);
    fillArrRandomly(arr, arrSize);

    printf("\nВывод массива:\n");
    printArrF(arr, arrSize, 1);

    printf("\nМинимальное число в массиве: %.3lf", arr[minIndF(arr, arrSize)]);

    return 0;
}
