#include <iostream>

int main()
{
	// 5 лабораторная работа, рисунок 5 и
	float x, y;

	printf("Введите x: "); scanf_s("%f", &x);
	printf("Введите y: "); scanf_s("%f", &y);

	if ((y >= abs(x) && abs(x) <= 1) or (y >= 1)) printf("\nYeah\n");

	return 0;
}