#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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
        printf("\nВвод: "); scanf_s("%d", &option);

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

int askUserAboutWritingArray()
{
    char options[][MAX_STRING_LEN_OPTIONS] = {
        "сохранить массив в текстовый файл",
        "сохранить массив в бинарный файл",
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
        printf("%s: ", title); scanf_s("%d", &n);
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
    arr[num] = NULL;
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

int getSizeArray2D(float** arr)
{
    int size = 0;
    while (arr[size++] != NULL);
    return size;
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

void fillArrayManually(float** arr)
{
    int cols;
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
        printf("Введите количество строк массива: "); scanf_s("%d", &rows);
        arr = reallocArray2D(arr, rows);
        fillArrayManually(arr);
        break;
    case 2:
        arr = getArrayFromFile(arr, filename);
        break;
    case 3:
        arr = getArrayFromBinFile(arr, filenameBin);
        break;
    case 4:
        exit(0);
        break;
    }
    
    printArray2D(arr);

    switch (askUserAboutWritingArray())
    {
    case 1:
        writeArrayToFile(arr, filename);
        break;
    case 2:
        writeArrayToBinFile(arr, filenameBin);
        break;
    }
    
    freeArray(arr);
    
    return 0;
}
