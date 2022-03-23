#include <stdio.h>

int main()
{
	/* Задание: вычислить частичную сумму ряда согласно варианту.В процессе
	суммирования выводить на экран также все текущие элементы ряда */
	int n = 0, st = -1;
	double x, res = 0;

	printf("Введите значение x: "); scanf_s("%lf", &x);
	do {
		printf("Введите n: "); scanf_s("%i", &n);
	} while (n < 1);

	for (int i = 1; i <= n; i++)
	{
		st *= -1;
		res += st * 2 * x;
	}

	printf("Результат: %lf", res);
	
	return 0;
}