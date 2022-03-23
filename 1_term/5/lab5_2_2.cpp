#include <iostream>

int main()
{
	float x;

	printf("Введите аргумент: ");
	scanf_s("%f", &x);

	if (x < 0)  x = x * x * x * x;
	if (x > 10) x = sin(x) / cos(x);
	if (0 <= x && x <= 10) x = 5 * sin(x);

	printf("Результат %f", x);

	return 0;
}