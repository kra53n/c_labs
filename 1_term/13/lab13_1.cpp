#include <ctime>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Задание: вычислить среднее геометрическое элементов массива. Поменять
местами элементы, стоящие на четных и нечетных позициях. */

int scanArraySize(int maxSize) {
	int n;
	do {
		printf("\nВыберите длину массива: ");
		scanf_s("%d", &n);
	} while (n < 1 || n > maxSize);
	return n;
}

void printArrayElements(float arr[], int size)
{
	for (int i = 0; i < size; i++)
		printf("arr[%d] = %f\n", i, arr[i]);
}

void fillArrayRandomNumbers(float arr[], int size, int start, int end)
{
	for (int i = 0; i < size; i++)
		arr[i] = rand() % (end - start + 1) + start;
}

void fillArrayManually(float arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("arr[%d] = ", i); scanf_s("%f", &arr[i]);
	}
}

void swapOddEvenArrayElements(float arr[], int size)
{
	for (int i = 0; i < size - 1; i += 2) {
		arr[i] = arr[i] + arr[i+1];
		arr[i+1] = arr[i] - arr[i+1];
		arr[i] = arr[i] - arr[i+1];
	}
}

float geometricMeanArrayElements(float arr[], int size)
{
	float product = 1;
	for (int i = 0; i < size; i++) product *= arr[i];
	return pow(product, 1.0 / size);
}

bool isFillArrayRandomly()
{
	int choice;
	do {
		printf("Выберите способ заполнения массива:\n");
		printf("\t1) с клавиатуры\n");
		printf("\t2) случайными числами из отрезка [a; b]\n");
		printf("Выбор: "); scanf_s("%d", &choice);
	} while (choice < 1 || choice > 2);
	return choice - 1;
}

int firstIndexArrayElementEqual0(float arr[], int size)
{
	for (int i = 0; i < size; i++)
		if (arr[i] == 0.)
			return i;
	return -1;
}

int main()
{
	int const arrSizeMax = 100;
	float arr[arrSizeMax];

	int arrSize   = scanArraySize(arrSizeMax);
	bool randomly = isFillArrayRandomly();

	if (randomly)
	{
		srand(time(NULL));
		int start, end;
		printf("\nВыбор концов отрезка генерации рандомных чисел.");
		do {
			printf("\nВведите начало отрезка: "); scanf_s("%d", &start);
			printf("Введите конец отрезка: ");    scanf_s("%d", &end);
		} while (start >= end || start < 0);
		fillArrayRandomNumbers(arr, arrSize, start, end);
	}
	else fillArrayManually(arr, arrSize);

	printf("\nМассив до смены чётных и нечётных элементов.\n");
	printArrayElements(arr, arrSize);

	swapOddEvenArrayElements(arr, arrSize);
	printf("\nМассив после смены чётных и нечётных элементов.\n");
	printArrayElements(arr, arrSize);

	printf("\nСреднее геометрическое элементов массива: %f\n",
		geometricMeanArrayElements(arr, arrSize));

	return 0;
}