#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>

/* Задание:
 * Массив представляется указателем на вектор указателей на
 * строки. Количество строк определяется терминальным символом.
 * Количество элементов строки определяется терминальным символом.
 * Память выделяется одним блоком */

const int MAX_STRING_LEN_OPTIONS = 100;

int askUserOptions(
    char const title[],
    char options_names[][MAX_STRING_LEN_OPTIONS],
    int elems_num,
    int offset = 1
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

float** mallocArray2D(float** arr)
{
    arr = (float**)malloc(sizeof(float*));
    if (arr == NULL)
    {
        printf("Ошибка выделения памяти!");
        exit(1);
    }
    return arr;
}

float** reallocArray2D(float** arr, int num)
{
    arr = (float**)realloc(arr, sizeof(float*) * (num + 1));
    if (arr == NULL)
    {
        printf("Ошибка выделения памяти!");
        exit(1);
    }
    return arr;
}

void mallocArray2DForArray(float** arr, int row, int cols)
{
    arr[row] = (float*)malloc(sizeof(float) * cols);
    if (arr[row] == NULL)
    {
        printf("Ошибка выделения памяти!");
        exit(1);
    }
    arr[row][cols] = 0;
}

void freeArray(float** arr)
{
    for (int row = -1; arr[row] != NULL; ++row)
        free(arr[row]);
    free(arr);
}

void fillArrayManually(float** arr)
{
    int cols;
    for (int row = 0; arr[row] != NULL; row++)
    {
        printf("Is problem here?\n");
        printf("[%d] ", row);
        cols = askUserAboutNumber("Введите количество элементов для строки");
        mallocArray2DForArray(arr, row, cols);

        for (int col = 0; arr[row][col] != 0; col++)
        {
            printf("arr[%d][%d] = ", row + 1, col + 1);
            scanf("%f", &arr[row][col]);
        }

        printf("\n");
    }
}

void printArray2D(float** arr)
{
    printf("\nМассив:\n");
    for (int row = 0; arr[row] != NULL; row++)
    {
        for (int col = 0; arr[row][col] != 0; col++)
            printf("\t%7.2f", arr[row][col]);
        printf("\n");
    }
}

errno_t fillArrayFromFile(float** arr, int& rows, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "r")) return 1;

    fscanf(f, "%d\n", &rows);

    for (int row = 0; row < rows; row++)
    {
        int col = 0;
        do {
            fscanf(f, "%7.2f ", &arr[row][col]);
        } while (arr[row][col++]);
        fscanf(f, "\n");
    }

    fclose(f);
    return 0;
}

errno_t writeMatrixToFile(float** arr, int rows, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "w")) return 1;

    fprintf_s(f, "%d\n", rows);

    for (int row = 0; row < rows; row++)
    {
        int col = 0;
        do {
            fprintf_s(f, "%7.2f ", &arr[row][col]);
        } while (arr[row][col++]);
        fprintf_s(f, "\n");
    }

    return 0;
}

errno_t fillArrayFromBinFile(float** arr, int &rows, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "rb")) return 1;

    fread(&rows, sizeof(int), 1, f);

    int cols;
    for (int row = 0; row < rows; row++)
    {
        fread(&cols, sizeof(float), 1, f);
        fread(&arr[row], sizeof(float), cols, f);
    }

    return 0;
}

int main()
{
    float** arr = NULL;
    arr = mallocArray2D(arr);

    char filename[] = "im_file.txt";
    char filenameBin[] = "im_file.bin";

    int rows = 0;
    switch (askUserAboutFillingArray())
    {
    case 1:
        printf("Введите количество строк массива: "); scanf("%d", &rows);
        arr = reallocArray2D(arr, rows);
        fillArrayManually(arr);
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        exit(0);
        break;
    }

    printArray2D(arr);
    freeArray(arr);

    printf("\n");
    return 0;
}
