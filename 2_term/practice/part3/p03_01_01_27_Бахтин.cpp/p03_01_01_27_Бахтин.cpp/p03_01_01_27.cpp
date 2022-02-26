#include <stdio.h>
#include <math.h>

float askUserNum()
{
	float num;
	do {
		printf("Введите ненулевое число: "); scanf_s("%f", &num);
	} while (num == 0);
	return num;
}

float sum()
{
	float sum = 0, term;
	int k = 0;
	float e = 0.00001;
	float x = askUserNum();

	do {
		term = x * x * x / 27 / (k + 2);
		sum += term;
		k++;
	} while (fabs(term) > e);
	return sum;
}

int main()
{
	printf("Сумма: %f", sum());
	return 0;
}