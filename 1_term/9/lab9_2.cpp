#include <stdio.h>
#include <math.h>

int main()
{
	/*
	Задание:
	Взяв за основу программу, написанную для решения Задачи 2 лабораторной
	работы №5 (вычисление значений кусочно-заданной функции). Доработать программу
	так, чтобы она выполняла табулирование функции, то есть вычисление и вывод ее
	значений при изменении аргумента от некоторого начального значения A до
	некоторого конечного значения B (включая А и В) с определенным шагом C.
	Параметры А, В и С вводятся с клавиатуры и могут быть дробными числами
	*/
	float a, b, c, res;

	printf("Введите начальное значение: "); scanf_s("%f", &a);
	do {
		printf("Введите шаг: "); scanf_s("%f", &c);
	} while (c <= 0);

	do {
		printf("Введите конечное значение: "); scanf_s("%f", &b);
	} while (a > b);

	printf("__________________________________\n");
	printf("| Число\t | x\t | y\t\t |\n");
	printf("|--------|-------|---------------|\n");

	for (int i = 1; a <= b; a += c, i++) {
		if (a < 0) res = a * a * a * a;
		else if (a > 10) res = tan(a);
		else res = 5 * sin(a);

		printf("| %i\t | %.1f\t | %.6f\t |\n", i, a, res);
	}

	printf("----------------------------------\n");

	return 0;
}
