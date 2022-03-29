#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "dynamic_array.h"

int askUserAboutNumber(char const title[])
{
    int n;
    bool cond;
    do {
        printf("%s: ", title); scanf_s("%d", &n);
        cond = n < 1;
        if (cond)
            printf("Было введено неверное число, оно должно быть больше 0. Попробуйте снова!\n");
    } while (cond);
    return n;
}

float** mallocArray2D()
{
    float** arr = (float**)malloc(sizeof(float*));
    if (arr == NULL)
    {
        printf("Ошибка выделения памяти!");
        exit(1);
    }
    return arr;
}

int getArray2DSize(float** arr)
{
    int row;
    for (row = 0; arr[row] != NULL; row++);
    return row;
}

float** reallocArray2D(float** arr, int num)
{
    arr = (float**)realloc(arr, sizeof(float*) * (num + 1));
    if (arr == NULL)
    {
        printf("Ошибка выделения памяти!");
        exit(1);
    }
    arr[num] = NULL;
    return arr;
}

float** getArray2DWithAddedRow(float** arr, int row, int cols)
{
    int rows = getArray2DSize(arr) + 1;
    arr = reallocArray2D(arr, rows);

    for (int i = rows, j = i - 1; i > row; i--, j--)
        arr[i] = arr[j];

    mallocArray2DForArray(arr, row, cols);
    arr[rows + 1] = NULL;
    return arr;
}

float** getArray2DWithDeletedRow(float** arr, int row)
{
    free(arr[row]);

    int size = getArray2DSize(arr);
    for (int i = row, j = i + 1; i <= size; i++, j++)
        arr[i] = arr[j];
    
    arr = reallocArray2D(arr, size-1);
    return arr;
}

void mallocArray2DForArray(float** arr, int row, int cols)
{
    arr[row] = (float*)malloc(sizeof(float) * (cols + 1));
    if (arr[row] == NULL)
    {
        printf("Ошибка выделения памяти!");
        exit(1);
    }
    arr[row][cols] = NULL;
}

void printArray2D(float** arr)
{
    printf("\nМассив:\n");
    for (int row = 0; arr[row] != NULL; row++)
    {
         for (int col = 0; arr[row][col] != NULL; col++)
            printf("\t%7.2f", arr[row][col]);
        printf("\n");
    }
    printf("\n");
}

void freeArray(float** arr)
{
    for (int row = 0; arr[row] != NULL; row++)
        free(arr[row]);
    free(arr);
}

float** getFilledArrayManually(float** arr)
{
    int rows, cols;

    printf("Введите количество строк массива: "); scanf_s("%d", &rows);
    arr = reallocArray2D(arr, rows);

    for (int row = 0; arr[row] != NULL; row++)
    {
        printf("[%d] ", row + 1);
        cols = askUserAboutNumber("Введите количество элементов для строки");
        mallocArray2DForArray(arr, row, cols);

        for (int col = 0; arr[row][col] != NULL; col++)
        {
            printf("arr[%d][%d] = ", row + 1, col + 1);
            scanf_s("%f", &arr[row][col]);
        }
        printf("\n");
    }
    return arr;
}

float** getArrayFromFile(float** arr, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "r")) exit(1);

    int row = 0;
    int cols = 0;
    int pos = ftell(f);
    while (!feof(f))
    {

        char currentChar = fgetc(f);
        if (currentChar == '.') cols++;
        if (currentChar == '\n')
        {
            arr = reallocArray2D(arr, row + 1);
            arr[row] = (float*)malloc(sizeof(float) * (cols + 1));

            fseek(f, pos, SEEK_SET);
            for (int col = 0; col < cols; col++)
                fscanf_s(f, "%f", &arr[row][col]);
            fscanf_s(f, "\n");
            pos = ftell(f);

            arr[row][cols] = NULL;
            cols = 0;
            row++;
        }
    }
    fclose(f);

    return arr;
}

errno_t writeArrayToFile(float** arr, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "w")) return 1;

    for (int row = 0; arr[row] != NULL; row++)
    {
        for (int col = 0; arr[row][col] != NULL; col++)
        {
            fprintf_s(f, "%7.2f", arr[row][col]);
        }
        fprintf_s(f, "\n");
    }
    return 0;
}

float** getArrayFromBinFile(float** arr, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "rb")) exit(1);

    int row = 0, col = 0;
    arr = reallocArray2D(arr, row);
    float value;
    while (!feof(f))
    {
        fread(&value, sizeof(float), 1, f);
        if (value == NULL)
        {
            row++;
            arr = reallocArray2D(arr, row);
            col = 0;
        }
        else
        {
            arr[row] = (float*)realloc(arr[row], sizeof(float) * (col + 2));
            arr[row][col++] = value;
            arr[row][col] = NULL;
        }
    }

    return arr;
}

errno_t writeArrayToBinFile(float** arr, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "wb")) return 1;

    for (int row = 0; arr[row] != NULL; row++)
    {
        int col = 0;
        while (arr[row][col] != NULL)
            fwrite(&arr[row][col++], sizeof(float), 1, f);
        fwrite(&arr[row][col], sizeof(float), 1, f);
    }

    return 0;
}
