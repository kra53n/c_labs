#include <stdio.h>
#include <math.h>

int fact(int x)
{
	if (x == 0) return 1;
	return x * fact(x - 1);
}

int main()
{
	/* Задание: Вычислить приближённую сумму ряда с заданной точностью
	согласно варианту.В процессе суммирования выводить на экран также все
	текущие элементы ряда */
	int i = 1, sign = -1, x;
	double result = 0, e, accur;
	
	do {
		printf("введите значение параметра: "); scanf_s("%i", &x);
	} while (x < -1);
	printf("введите точность: "); scanf_s("%lf", &e);

	double numerator = fact(x + 1);
	double denominator;

	do {
		denominator = 1;
		for (int j = 0; j < i; j++) denominator *= i;
		accur = sign * (numerator / denominator);
		result += accur;
		sign *= -1;
		i++;
	} while (fabs(accur) > e);

	printf("%lf", result);
	
	return 0;
}