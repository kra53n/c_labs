#include<iostream>

int main()
{
	double x, res;

	printf("Введите x: ");
	scanf_s("%lf", &x);

	res = ((2 * (pow(x, 2) + 3)) / (pow(x, 2) - 2 * x + 5));
	printf("Результат: %lf", res);

	return 0;
}