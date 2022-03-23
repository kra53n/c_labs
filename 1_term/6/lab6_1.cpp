#include <stdio.h>

int main()
{
	// Задание:
	// Дано двузначное число. Вывести его название в текстовой форме
	int n;

	printf("Введите число: ");  scanf_s("%d", &n);

	if (n < 10 || n > 99) return 1;

	switch (n)
	{
	case 10: printf("Десять");       break;
	case 11: printf("Одиннадцать");  break;
	case 12: printf("Двенадцать");   break;
	case 13: printf("Тринадцать");   break;
	case 14: printf("Чертрнадцать"); break;
	case 15: printf("Пятнадцать");   break;
	case 16: printf("Шестнадцать");  break;
	case 17: printf("Семнадцать");   break;
	case 18: printf("Восемнадцать"); break;
	case 19: printf("Девятнадцать"); break;

	default:
	{
		switch (n / 10)
		{
		case 2: printf("Двадцать");   break;
		case 3: printf("Тридцать");   break;
		case 4: printf("Сорок");      break;
		case 5: printf("Пятьдесят");  break;
		case 6: printf("Шесдесят");   break;
		case 7: printf("Семдесят");   break;
		case 8: printf("Восемдесят"); break;
		case 9: printf("Девяносто");  break;
		}

		printf(" ");
		switch (n % 10)
		{
		case 1: printf("один");   break;
		case 2: printf("два");    break;
		case 3: printf("три");    break;
		case 4: printf("четрые"); break;
		case 5: printf("пять");   break;
		case 6: printf("шесть");  break;
		case 7: printf("семь");   break;
		case 8: printf("восемь"); break;
		case 9: printf("девять"); break;
		}
	}
	}
	return 0;
}