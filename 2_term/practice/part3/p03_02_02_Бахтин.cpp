/* Выполнение 2 и 27 заданий файла "Практика_2_№3.pdf" */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int const MAX_STRING_LEN_OPTIONS = 100;

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
    
    printf("\nРезультат: %s\n\n", resstr, j);
}

float askUserNum()
{
	float num;
	do {
		printf("Введите ненулевое число: "); scanf("%f", &num);
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

int askUserOptions(
    char const title[],
    char options_names[][MAX_STRING_LEN_OPTIONS],
    int elems_num,
    int offset=1
)
{
    int option, cond;

    do {
        printf("%s\n", title);
        for (int i = 0; i < elems_num; i++)
            printf("\t%d) %s\n", i + offset, options_names[i]);
        printf("\nВвод: "); scanf("%d", &option);

        cond = 0 + offset > option || option > elems_num + offset - 1;
        if (cond)
            printf("\nВведено неверное число! Попробуйте снова.\n");
    } while (cond);

    return option;
}

int main()
{
    char menuOptions[][MAX_STRING_LEN_OPTIONS] = {
        "вставить пробелы строки в её центр",
        "вычислить сумму",
        "выход",
    };
    while (true)
        switch (askUserOptions(
            "Меню:", menuOptions,
            sizeof(menuOptions) / MAX_STRING_LEN_OPTIONS)
        )
        {
            case 1:
                insertingSpacesInStrCenter();
                break;
            case 2:
                printf("\n");
                printf("Полученная сумма: %f\n\n", sum());
                break;
            case 3:
                exit(0);
                break;
        }

    return 0;
}
