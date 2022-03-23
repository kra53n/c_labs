#include <stdio.h>

int main()
{
	/*
	Задание:
	Вычислить значение факториала целого числа по формуле а!=1·2·3·…·а
	*/
	int num_el, res = 1;
	
	do {
		printf("Введите число: "); scanf_s("%i", &num_el);
	} while (num_el < 0);

	if (num_el) for (int i = 1; i <= num_el; i++) res *= i;
	else res = 1;

	printf("Факториал числа %i: %i", num_el, res);

	return 0;
}