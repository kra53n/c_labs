#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* Задание:
 * Массив представляется указателем на вектор указателей на
 * строки. Количество строк определяется терминальным символом.
 * Количество элементов строки определяется терминальным символом.
 * Память выделяется одним блоком*/

const int MAX_STRING_LEN_OPTIONS = 100;

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

        cond = offset > option || option > elems_num + offset;
        if (cond)
            printf("\nВведено неверное число! Попробуйте снова.\n");
    } while (cond);

    return option;
}

int askUserAboutFillingArray()
{
    char options[][MAX_STRING_LEN_OPTIONS] = {
        "создать массив, заполнив вручную",
        "создать массив, заполнив рандомно",
        "загрузить массив из текстового файла",
        "загрузить массив из бинарного файла",
        "выход",
    };
    return askUserOptions("Выберите способ заполнения массива:",
        options, sizeof(options) / MAX_STRING_LEN_OPTIONS);
}

int askUserAboutNumber(char const title[])
{
    int n;
    bool cond;
    do {
        printf("%s: ", title); scanf("%d", &n);
        cond = n < 1;
        if (cond)
            printf("Было введено неверное число, оно должно быть больше 0. Попробуйте снова!\n");
    } while (cond);
    return n;
}

void createAndFillArrayManually(float **arr, int rows)
{
    arr = (float**)malloc(sizeof(float*) * rows);
    for (int row = 0; row < rows; row++)
    {
        int col = 0;
        do {
            arr[row] = (float*)realloc(arr, sizeof(float) * (col+1));
            printf("arr[%d][%d] = ", row+1, col+1); scanf("%f", &arr[row][col]);
        } while (arr[row][col]);
    }
}

void printArray2D(int **arr)
{
}

int main()
{
    float **arr;

    switch (askUserAboutFillingArray())
    {
        case 1:
        {
            int rows = askUserAboutNumber("\nВведите количество строк");
            createAndFillArrayManually(arr, rows);
            break;
        }
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            exit(0);
            break;
    }

    printf("\n");
    return 0;
}
