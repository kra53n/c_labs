#include <stdio.h>
#include <math.h>

int main() {
	int x; double f;

	scanf_s("%d", &x);
	if (x < 0) f = 2 * x + 3;
	if ((x > 0) && (x < 5)) f = x * x;
	if (x == 5) f = 0;
	if (x > 5) f = sin(double(x));

	printf("%lf", f);

	return 0;
}