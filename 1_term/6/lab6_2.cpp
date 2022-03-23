#define _USE_MATH_DEFINES
#include <iostream>

float max(float a, float b)
{
	return a > b ? a : b;
}

int main()
{
	// Заданы радиусы пяти окружностей. Определить и вывести максимальную
	// из длин этих окружностей

	float r1, r2, r3, r4, r5, res;

	scanf_s("%f", &r1);
	scanf_s("%f", &r2);
	scanf_s("%f", &r3);
	scanf_s("%f", &r4);
	scanf_s("%f", &r5);

	res = max(r1, r2);
	res = max(res, r3);
	res = max(res, r4);
	res = max(res, r5);

	res *= 2 * M_PI;

	printf("Максимальная длина окружности: %f", res);

	return 0;
}
