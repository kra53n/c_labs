#include <iostream>

int main()
{
	// Задание:
	// Текущее показание электронных часов m часов (0 <= m <= 23), n минут
	// (0 <= n <= 59), k секунд (0 <= k <= 59). Какое вермя будут показывать
	// часы через p часов q минут r секунд(p > 0, q > 0, r > 0)?

	int m, n, k;
	int p, q, r;
	int seconds, minutes, hours;

	printf("Введите количество часов от 0 до 23: "); scanf_s("%d", &m);
	printf("Введите количество минут от 0 до 59: "); scanf_s("%d", &n);
	printf("Введите количество секунд от 0 до 59: "); scanf_s("%d", &k);
	printf("\n");

	printf("Введите: сколько часов прошло(больше 0): "); scanf_s("%d", &p);
	printf("Введите: сколько минут прошло(больше 0): "); scanf_s("%d", &q);
	printf("Введите: сколько секунд прошло(больше 0): "); scanf_s("%d", &r);
	printf("\n");

	seconds = k + r;
	minutes = n + q + (seconds / 60);
	hours   = m + p + (minutes / 60);

	seconds %= 60;
	minutes %= 60;
	hours   %= 24;

	printf("Время: %d часов %d минут %d секунд: ", hours, minutes, seconds);

	return 0;
}