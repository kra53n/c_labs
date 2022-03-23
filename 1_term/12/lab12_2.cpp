#include <stdio.h>

int main() {
	int yearG = 100, previousYearG = 100, hold, TotalDays = 16, grams = 0;

	for (int i = 2; i < TotalDays; i++)
	{
		hold = yearG;
		yearG += previousYearG;
		previousYearG = hold;
	}

	printf("\nНа своём %d дне рождения Винни-Пух съест %d,%d кг\n",
		TotalDays, yearG / 1000, yearG % 1000);

	return 0;
}