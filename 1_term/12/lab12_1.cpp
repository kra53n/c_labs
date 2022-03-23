#include <stdio.h>

/* Задание: 2.	На каждом следующем дне рождения Винни - Пух съедает столько же
пищи что и на двух предыдущих.На двух первых днях рождения у Пятачка и
Кролика он съел по 100 г пищи.Определить, сколько килограммов пищи
Винни - Пух съест на пятнадцатом дне рождения. */

int how_much_eat_on_birthday(int year, int level) {
	printf("Текущий уровень рекурсии: %d\tЗначение year: %d\n", level, year);
	level++;

	if (year == 1 || year == 2) return 100;
	return how_much_eat_on_birthday(year - 1, level) + \
		how_much_eat_on_birthday(year - 2, level);
}

int main() {
	int year = 16, grams = how_much_eat_on_birthday(year, 1);

	printf("\nНа своём %d дне рождения Винни-Пух съест %d,%d кг\n",
		year, grams / 1000, grams % 1000);

	return 0;
}