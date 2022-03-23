#include <iostream>

int main()
{
	// 5 лабораторная работа, рисунок 5 а
	float x, y;
	
	printf("Введите координату x: "); scanf_s("%f", &x);
	printf("Введите координату y: "); scanf_s("%f", &y);

	if ((x >= 0) && (x * x + y * y >= 4) && (x * x + y * y <= 16) or
		(y <= -2 && y >= -4 && abs(x) >= 2 && abs(x) <= 4)) printf("\nYeah\n");

	return 0;
}