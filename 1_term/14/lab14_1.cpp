#include <ctime>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Задание: вычислить среднее геометрическое элементов массива. Поменять
местами элементы, стоящие на четных и нечетных позициях. */

int scanArraySize(int maxSize)
{
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
	float tmp;
	for (int i = 0; i < size - 1; i += 2) {
		tmp = arr[i];
		arr[i] = arr[i+1];
		arr[i+1] = tmp;
	}
}

float geometricMeanArrayElements(float arr[], int size)
{
	float product = 1;
	for (int i = 0; i < size; i++) product *= arr[i];
	return pow(product, 1.0 / size);
}

int scanArrayFromFile(char filename[], float arr[])
{
	FILE* f;
	if (fopen_s(&f, filename, "r"))
	{
		printf("\nCouldn't open file %s!", filename);
		exit(1);
	}

	int size;
	fscanf_s(f, "%d", &size);

	for (int i = 0; i < size; i++) fscanf_s(f, "%f", &arr[i]);

	fclose(f);
	return size;
}

int writeArrayToFile(const char filename[], float arr[], int size)
{
	FILE* f;
	if (fopen_s(&f, filename, "w"))
	{
		printf("Couldn't write file %s!", filename);
		return 1;
	}
	
	fprintf(f, "%d\n", size);
	for (int i = 0; i < size; i++) fprintf(f, "%f\n", arr[i]);

	fclose(f);
	return 0;
}

int selectArrayFillingMethod()
{
	int choice;
	do {
		printf("Выберите способ заполнения массива:\n");
		printf("\t1) с клавиатуры\n");
		printf("\t2) случайными числами из отрезка [a; b]\n");
		printf("\t3) из файла\n");
		printf("Выбор: "); scanf_s("%d", &choice);
	} while (choice < 1 || choice > 3);
	return choice;
}

int main()
{
	int const arrSizeMax = 100;
	float arr[arrSizeMax];
	int arrSize;

	char inputFilename[]  = "im_file.txt";
	char outputFilename[] = "maybe_im_not_a_file.txt";

	switch (selectArrayFillingMethod()) {
	case 1:
		arrSize = scanArraySize(arrSizeMax);
		fillArrayManually(arr, arrSize);
		break;
	case 2:
		arrSize = scanArraySize(arrSizeMax);
		int start, end;
		srand(time(NULL));

		printf("\nВыбор концов отрезка генерации рандомных чисел.");
		do {
			printf("\nВведите начало отрезка: "); scanf_s("%d", &start);
			printf("Введите конец отрезка: ");    scanf_s("%d", &end);
		} while (start >= end || start < 0);

		fillArrayRandomNumbers(arr, arrSize, start, end);
		break;
	case 3:
		arrSize = scanArrayFromFile(inputFilename, arr);
		break;
	}

	printf("\nМассив до смены чётных и нечётных элементов.\n");
	printArrayElements(arr, arrSize);

	swapOddEvenArrayElements(arr, arrSize);
	printf("\nМассив после смены чётных и нечётных элементов.\n");
	printArrayElements(arr, arrSize);

	printf("\nСреднее геометрическое элементов массива: %f\n",
		geometricMeanArrayElements(arr, arrSize));

	writeArrayToFile(outputFilename, arr, arrSize);

	return 0;
}