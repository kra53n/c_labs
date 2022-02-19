#include <stdlib.h>
#include <stdio.h>

int scanArrSize(int arrMinSize, int arrMaxSize)
{
    int size;
    do {
        printf("\nВведите размер массива от [%d;%d]: ", arrMinSize, arrMaxSize);
        scanf("%d", &size);
        if (size < arrMinSize || size > arrMaxSize)
            printf("Введённый размер некорректен. Попробуйте ввести его снова.");
    } while (size < arrMinSize || size > arrMaxSize);

    return size;
}

void fillArrRandomlyF(double arr[],  int size)
{
    for (int i = 0; i < size; i++)
        arr[i] = (rand() * rand()) / 1000.;
}

void scanArrManuallyF(double arr[], int size, int offset=0)
{
    for (int i = 0; i < size; i++)
    {
        printf("arr[%2d] = ", i+offset); scanf("%lf", &arr[i]);
    }
}

void printArrF(double arr[], int size, int offset=0)
{
    for (int i = 0; i < size; i++)
        printf("arr[%2d] = %12.3lf\n", i+offset, arr[i]);
}

int minIndF(double arr[], int size)
{
    int min = 0;
    for (int i = 1; i < size; i++)
        min = arr[min] > arr[i] ? i : min;
    return min;
}

int maxIndF(double arr[], int size)
{
    int max = 0;
    for (int i = 1; i < size; i++)
        max = arr[max] < arr[i] ? i : max;
    return max;
}

void fillArrRandomly(int arr[], int size, int min, int max)
{
    for (int i = 0; i < size; i++)
        arr[i] = rand() % (max - min + 1) + min;
}

void scanArrManually(int arr[], int size, int offset=0)
{
    for (int i = 0; i < size; i++)
    {
        printf("arr[%2d] = ", i+offset); scanf("%d", &arr[i]);
    }
}

void printArr(int arr[], int size, int offset=0)
{
    for (int i = 0; i < size; i++)
        printf("arr[%d] = %d\n", i+offset, arr[i]);
}
