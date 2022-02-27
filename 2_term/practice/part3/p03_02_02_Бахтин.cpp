/* Выполнение 2 и 27 заданий файла "Практика_2_№3.pdf" */

#include <stdio.h>
#include <math.h>

void scanStr(char str[])
{
    printf("Введите строку: "); scanf("%[^\n]%*c", str);
}

void insertingSpacesInStrCenter()
{
    char str[100];
    char resstr[100];
    scanStr(str);

    int i, j;
    int numspaces = 0;
    for (i = j = 0; str[i] != 0; i++)
        if (str[i] != ' ')
            resstr[j++] = str[i];
        else
            numspaces++;
    resstr[j] = '\0';

    while (i > j/2)
        resstr[i--] = resstr[i-numspaces];
    while (i - j/2 < numspaces)
        resstr[i++] = ' ';
    
    printf("%s\n", resstr, j);
}

float askUserNum()
{
	float num;
	do {
		printf("Введите ненулевое число: "); scanf_s("%f", &num);
	} while (num == 0);
	return num;
}

float sum()
{
	float sum = 0, e = 0.00001, term;
	float x = askUserNum();
	int k = 0;

	do {
		term = x*x / 4 / (k + 1) / (k + 2);
		sum += term;
		k++;
	} while (fabs(term) > e);

	return sum;
}

int main()
{
    insertingSpacesInStrCenter();
    return 0;
}
