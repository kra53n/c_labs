#include <stdio.h>

int main()
{
	// Задание:
	// Взяв за основу свою программу, написанную для решения Задачи 2
	// лабораторной работы №7, доработать её, организовав проверку корректности
	// введенного значения с помощью цикла с постусловием
	// 
	// Дано целое положительное число. Определить среднее арифметическое его цифр
	int number, digits_number = 0;
	float res = 0;

	do {
		printf("Введите число: "); scanf_s("%d", &number);
	} while (number < 1);

	while (number > 0)
	{
		res += number % 10;
		number /= 10;
		digits_number++;
	}

	res /= digits_number;

	printf("%f", res);

	return 0;
}