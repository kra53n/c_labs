#include <stdio.h>
#include <math.h>

int main()
{
	/* Задание:
	*  Дано натуральное число n. Составить программу вычисления выражения
	*  1^1 + 1^2 + ... + 1^n + 2^1 + 2^2 + ... + 2^n + n^1 + n^2 + n^n
	*/
	int n, res = 0;

	do {
		printf("Введите число: "); scanf_s("%d", &n);
	} while (n < 1);

	for (int i = 1; i <= n; i++)
	{
		int power = i;
		for (int j = 1; j <= n; j++)
		{
			res += power;
			power *= i;
		}
	}

	printf("Результат: %d", res);

	return 0;
}