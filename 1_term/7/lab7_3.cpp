#include <stdio.h>

int main()
{
	int a, res = 0, b = 0, place = 1;

	printf("Введите число: "); scanf_s("%d", &a);

	while (b < 2 || b > 9)
	{
		printf("Введите основание системы счисления: "); scanf_s("%d", &b);
	}

	while (a > 0)
	{
		res += a % b * place;
		a /= b;
		place *= 10;
	}

	printf("В %d-ой системе счисления: %d", b, res);

	return 0;
}