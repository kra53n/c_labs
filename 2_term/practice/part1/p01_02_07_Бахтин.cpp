#include <stdio.h>
#include "popular_func.h"

/* Название файла с заданием: 02_praktika_05.02.2022
 * Задание:
 * Дан массив целых чисел. Определить
 *   а) количество элементов, отличных от последнего элемента
 *   б) количество элементов, кратных a
*/

int elemNumOtherThanElem(int arr[], int size, int ind)
{
    int num = 0;
    for (int i = 0; i < size; i++)
        if (arr[i] != arr[ind]) num += 1;
    return num;
}

int elemNumMultiplesNum(int arr[], int size, int mult)
{
    int num = 0;
    for (int i = 0; i < size; i++)
        if (arr[i] % mult == 0) num += 1;
    return num;
}

int main()
{
    int arrSize = scanArrSize(2, 10);
    int arr[10];

    printf("Введите значения массива:\n");
    scanArrManually(arr, arrSize, 1);

    printf("\nКоличество элементов отличных от последнего: %d",
        elemNumOtherThanElem(arr, arrSize, arrSize-1));
    
    int a;
    printf("\n\nВведите число, чтобы посчитать скольким элементам массива оно кратно: ");
    scanf("%d", &a);

    printf("Количество элементов кратных %d: %d", a,
        elemNumMultiplesNum(arr, arrSize, a));

    return 0;
}
