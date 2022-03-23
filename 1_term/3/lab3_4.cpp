#include<iostream>

int main()
{
	float a, b;

	scanf_s("%f", &a);
	a = a * a;
	a = a * a;
	printf("%f\n\n", a);

	scanf_s("%f", &a);
	b = a * a;     // a^2
	b = b * b * b; // a^6
	b = b * b * a; // a^13
	printf("%f\n\n", b);

	scanf_s("%f", &a);
	b = a * a;     // a^2
	b = b * b * b; // a^6
	printf("%f\n\n", b);

	scanf_s("%f", &a);
	b = a * a * a;     // a^3
	b = b * b * b * b; // a^15
	printf("%f\n\n", b);

	scanf_s("%f", &a);
	b = a * a;     // a^2
	b = b * b * a; // a^5
	b = b * b * b; // a^15
	printf("%f\n\n", b);

	scanf_s("%f", &a);
	b = a * a * a;     // a^3
	printf("%f", &b);
	b = b * b; // a^6
	b = b * b * b; // a^15
	printf("%f\n\n", b);

	return 0;
}