#include <stdio.h>

int my_pow(int a, int b)
{
	int res = 1;

	for (int i = 0; i < b; i++)
	{
		res *= a;
	}

	return res;
}

int main()
{
	int a, b = 0, place = 0, res = 0;

	printf("Введите число: "); scanf_s("%d", &a);

	while (b < 2 || b > 9)
	{
		printf("Введите основание системы счисления: "); scanf_s("%d", &b);
	}

	while (a > 0)
	{
		res += a % 10 * my_pow(b, place);
		a /= 10;
		place++;
	}

	printf("%d", res);

	return 0;
}