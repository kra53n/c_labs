#include <iostream>

int main()
{
	// Задание:
	// Дана масса в граммах.  Выразить эту массу а) в полных тоннах;
	// б) в полных килограммах

	int grams, tons, kilograms;

	printf("Введите массу в граммах: ");
	scanf_s("%d", &grams);

	tons = grams / 1000000;
	kilograms = grams % 1000000 / 1000;

	printf("\nВ %d граммах %d тонн и %d килограмм.\n", grams, tons, kilograms);

	return 0;
}