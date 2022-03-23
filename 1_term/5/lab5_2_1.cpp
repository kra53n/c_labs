#include <iostream>
#include <math.h>

int main()
{
	float x;

	printf("Введите аргумент: ");
	scanf_s("%f", &x);

	if (x < 0)
		x = x * x * x * x;
	else { 
		if (x > 10)
			x = sin(x) / cos(x);
		else
			x = 5 * sin(x);
	}

	printf("Результат: %f", x);

	return 0;
}
