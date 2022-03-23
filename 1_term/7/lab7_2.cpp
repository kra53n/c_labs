#include <stdio.h>

int main()
{
	// Задание:
	// Дано целое положительное число. Определить среднее арифметическое его цифр
	int number, digits_number = 0;
	float res = 0;

	
	printf("Введите число: "); scanf_s("%d", &number);

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