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

int **initMatrix(int **arr, int &rows, int &cols)
{
    rows = askUserAboutNumber("Введите количество строк");
    cols = askUserAboutNumber("Введите количество столбцов");
    printf("\n");
    
    arr = (int**)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++)
    {
        arr[i] = (int*)malloc(cols * sizeof(int));

        for (int j = 0; j < cols; j++)
        {
            printf("arr[%2d][%2d] = ", i+1, j+1); scanf("%d", &arr[i][j]);
        }
    }

    return arr;
}

int **initFreeMatrix(int **arr, int &rows, int cols[])
{
    rows = askUserAboutNumber("Введите количество строк");

    arr = (int**)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++)
    {
        cols[i] = askUserAboutNumber("Введите количество столбцов");
        arr[i] = (int*)malloc(cols[i] * sizeof(int));
        printf("\n");

        for (int j = 0; j < cols[i]; j++)
        {
            printf("arr[%2d][%2d] = ", i+1, j+1); scanf("%d", &arr[i][j]);
        }
    }

    return arr;
}

void printArray2D(int **arr)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%5d ", arr[i][j]);
        printf("\n");
    }
}

int main()
{
    int **arr;

    switch (askUserAboutFillingArray())
    {
        case 1:
            break;
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
