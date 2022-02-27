/* Выполнение 2 задания  файла "Практика_3_№3.pdf" */
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
	float sum = 0, e = 0.00001, term;
	float x = askUserNum();
	int n = 0;

	do {
		term = x * x * x / 27 / (n + 2);
		sum += term;
		n++;
	} while (fabs(term) > e);

	return sum;
}

int main()
{
	printf("Сумма: %f", sum());
	return 0;
}
