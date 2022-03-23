#include <stdio.h>

int main()
{
	// Задание:
	// Даны целые числа А и В, A < B.Определить целое положительное число С,
	// такое, что A^C = B, если В – степень числа А, или вывести сообщение,
	// что такого числа не существует

	int a, b, mult = 1, c = 0;

	printf("A^C = B\n");
	printf("Введите число A: "); scanf_s("%d", &a);
	printf("Введите число B: "); scanf_s("%d", &b);

	for(int i = 0; i<10; i++)

	while (mult < b) {
		mult *= a;
		c++;
	}

	if (mult == b) printf("%i^%i = %i", a, c, b);
	else printf("%i - не степень числа %i", b, a);

	return 0;
}