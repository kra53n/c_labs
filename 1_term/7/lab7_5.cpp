#include <stdio.h>

int main()
{
	int last_digit, digit, res, number = 0, c = 0;

	while (number < 1) {
		printf("Введите номер элемента из последовательности Фибоначчи: ");
		scanf_s("%d", &number);
	}

	last_digit = 0; digit = 1;

	if (number > 3)
	{
		while (c != number - 2)
		{
			res = last_digit + digit;
			last_digit = digit;
			digit = res;
			c++;
		}
	}

	if (number == 1) res = 0;
	if (number == 2 || number == 3) res = 1;

	printf("\n%d", res);

	return 0;
}