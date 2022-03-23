#include <stdio.h>

int main()
{
	// Задание:
	// Написать программу перемножения введенных чисел до тех пор, пока
	// пользователь не введет 0
	float user_input, res = 1;

	do {
		printf("Введите число(0 - выход из программы): ");
		scanf_s("%f", &user_input);
		res *= user_input;
	} while (res != 0);

	printf("Результат: %f\n", res);

	return 0;
}