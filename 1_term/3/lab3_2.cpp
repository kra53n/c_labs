#include<iostream>

int main()
{
	// Задание:
	// Заданы координаты трех вершин треугольника (х1, у1), (х2, у2),
	// (х3, у3). Определить его периметр

	float x1, x2, x3;
	float y1, y2, y3;
	double res, a, b, c;

	printf("Введите x координаты вершин: \n");
	scanf_s("%f %f %f", &x1, &x2, &x3);
	printf("Введите y координаты вершин: \n");
	scanf_s("%f %f %f", &y1, &y2, &y3);

	a = sqrt(((x3 - x1) * (x3 - x1)) + ((y3 - y1) * (y3 - y1)));
	b = sqrt(((x3 - x2) * (x3 - x2)) + ((y3 - y2) * (y3 - y2)));
	c = sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

	res = (a + b + c);

	printf("Результат: %.3lf\n", res);

	return 0;
}