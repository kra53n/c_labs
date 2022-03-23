#include <iostream>

int main()
{
	// Задание:
	// Определить стоимость мебельного гарнитура, содержащего 4 стула,
	// 2 кресла и 1 стол. Цена изделий соответственно A, B и C.

	double A, B, C, x;

	printf("Введите A: ");
	scanf_s("%lf", &A);
	printf("Введите B: ");
	scanf_s("%lf", &B);
	printf("Введите C: ");
	scanf_s("%lf", &C);

	x = 4*A + 2*B + 1*C;

	printf("\n4 стула, 2 кресла и 1 стол: %lf\n", x);

	return 0;
}