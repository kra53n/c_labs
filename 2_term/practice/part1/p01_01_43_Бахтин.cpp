#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "popular_func.h"

/* Название файла с заданием: 01_praktika_05.02.2022
 * Задание:
 * Дан массив вещественных сулчайных чисел. Рамер - случайное число из
 * диапозона [5;12], элементы задаёт пользоыватель. Определить сумму чисел,
 * целая часть которых кратна трём.
*/

double elemsSumIsNumberMultiple(double arr[], int arrSize, int numMultiple, int offset=0)
{
    double sum = 0;
    for (int i = 0; i < arrSize; i++)
    {
        if ((int) arr[i] % numMultiple == 0)
        {
            printf("arr[%2d] = %12.3lf\n", i+offset, arr[i]);
            sum += arr[i];
        }
    }
    return sum;
}

int main()
{
    srand(time(0));
    int numberMultiple = 3;
    int arrSize = rand() % 8 + 5;
    double arr[12];

    printf("Введите массив из %d элементов:\n", arrSize);
    scanArrManuallyF(arr, arrSize, 1);

    printf("\nЭлементы, целая часть которых кратна %d:\n", numberMultiple);
    printf("Сумма элементов, целая часть которых кратна %d: %lf",
        numberMultiple, elemsSumIsNumberMultiple(arr, arrSize, numberMultiple, 1));

    return 0;
}
