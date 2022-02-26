#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>

int const MAX_STRING_LEN_OPTIONS = 50;
int const MAX_LEN_ARRAY = 100;

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

        cond = 0 + offset > option || option > elems_num + offset;
        if (cond)
            printf("\nВведено неверное число! Попробуйте снова.\n");
    } while (cond);

    return option;
}

int scanArrSize(int& size, int sizeMax, const char arrName[])
{
    do {
        printf("Введите количество %s [0;%d]: ", arrName, sizeMax);
        scanf_s("%d", &size);
    } while (size < 0 || size > sizeMax);
    return size;
}

float** mallocMatrix(int rows, int cols)
{
    float** matrix = (float**)malloc(rows * sizeof(float*));
    for (int i = 0; i < rows; i++)
        matrix[i] = (float*)malloc(cols * sizeof(float));
    return matrix;
}

void scanMatrixSize(int& rows, int& cols)
{
    scanArrSize(rows, MAX_LEN_ARRAY, "рядов");
    scanArrSize(cols, MAX_LEN_ARRAY, "столбцов");
}

void fillMatrixRandomly(float** matrix, int rows, int cols)
{
    srand(time(0));
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            matrix[i][j] = rand() / 100. - 100;
    }
}

errno_t fillMatrixFromFile(float** matrix, int& rows, int& cols, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "r")) return 1;

    fscanf_s(f, "%d %d\n", &rows, &cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            fscanf_s(f, "%10.5f ", &matrix[i][j]);
        fscanf_s(f, "\n");
    }

    fclose(f);
    return 0;
}

errno_t fillMatrixFromBinFile(float** matrix, int& rows, int& cols, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "rb")) return 1;

    fread(&rows, sizeof(int), 1, f);
    fread(&cols, sizeof(int), 1, f);

    for (int i = 0; i < rows; i++)
        fread(&matrix[i], sizeof(int), cols, f);

    return 0;
}

void outputMatrixToScreen(float** matrix, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%10.5f\t", matrix[i][j]);
        printf("\n");
    }
}

errno_t writeMatrixToFile(float** matrix, int rows, int cols, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "w")) return 1;

    fprintf_s(f, "%d %d\n", rows, cols);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            fprintf_s(f, "%10.5f ", matrix[i][j]);
        fprintf_s(f, "\n");
    }

    return 0;
}

errno_t writeMatrixToBinFile(float** matrix, int rows, int cols, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "wb")) return 1;

    fwrite(&rows, sizeof(int), 1, f);
    fwrite(&cols, sizeof(int), 1, f);

    for (int i = 0; i < rows; i++)
        fwrite(&matrix[i], sizeof(int), cols, f);

    return 0;
}

int countNegativeNums(float arr[], int size)
{
    int num = 0;
    for (int i = 0; i < size; i++)
        if (arr[i] < 0) num += 1;
    return num;
}
int countProductRowsWhereMoreThanOneNegativeNums(float** matrix, int rows, int cols)
{
    int count = 0, product = 1;

    for (int i = 0; i < rows; i++)
    {
        if (countNegativeNums(matrix[i], cols) > 0)
        {
            for (int j = 0; j < cols; j++)
                product *= matrix[i][j];
        }
    }

    return product;
}

float* arrOfRowsSumOfNegativeOddElems(
    float** matrix, int rows, int cols)
{
    float* arr = (float*)malloc(rows * sizeof(float));
    for (int i = 0; i < rows; i++)
    {
        int sum = 0;
        for (int j = 0; j < cols; j += 2)
            if (matrix[i][j] < 0)
                sum += matrix[i][j];
        arr[i] = sum;
    }
    return arr;
}

void sortRowsByIncreaseNumsNegativeOddElems(
    float** matrix, int rows, int cols)
{
    float* arrOfValues = arrOfRowsSumOfNegativeOddElems(matrix, rows, cols);

    for (int i = 0; i < rows - 1; i++)
    {
        float* tmpArr, tmp;
        for (int j = 0; j < cols - i - 1; j++)
        {
            if (arrOfValues[j] > arrOfValues[j + 1])
            {
                tmp = arrOfValues[j];
                arrOfValues[j] = arrOfValues[j + 1];
                arrOfValues[j + 1] = tmp;

                tmpArr = matrix[j];
                matrix[j] = matrix[j + 1];
                matrix[j + 1] = tmpArr;
            }
        }
    }
}

int main()
{
    float** matrix = mallocMatrix(MAX_LEN_ARRAY, MAX_LEN_ARRAY);
    int rows, cols;

    char filename[] = "im_file.txt";
    char filenameBin[] = "im_file.bin";

    char inputOptions[][MAX_STRING_LEN_OPTIONS] = {
        "из текстового файла",
        "из бинарного файла",
        "случайными числами",
        "выход",
    };

    switch (
        askUserOptions("Выберите способ ввода матрицы:", inputOptions,
            sizeof(inputOptions) / MAX_STRING_LEN_OPTIONS)
        )
    {
    case 1:
        fillMatrixFromFile(matrix, rows, cols, filename);
        break;
    case 2:
        fillMatrixFromBinFile(matrix, rows, cols, filenameBin);
        break;
    case 3:
        scanMatrixSize(rows, cols);
        fillMatrixRandomly(matrix, rows, cols);
        break;
    case 4:
        exit(0);
        break;
    }

    printf("\nМатрица:\n");
    outputMatrixToScreen(matrix, rows, cols);

    printf("\nПроизведение элементов в строках, где больше одного негативного числа: %d",
        countProductRowsWhereMoreThanOneNegativeNums(matrix, rows, cols));

    sortRowsByIncreaseNumsNegativeOddElems(matrix, rows, cols);
    printf("\n\nМатрица, строки которой были отсортированы по сумме отрицательных чисел:\n");
    outputMatrixToScreen(matrix, rows, cols);
    printf("\n");

    char outputOptions[][MAX_STRING_LEN_OPTIONS] = {
        "в текстовый файл",
        "в бинарный файла",
        "выход",
    };

    switch (
        askUserOptions("Выберите способ записи матрицы:", outputOptions,
            sizeof(outputOptions) / MAX_STRING_LEN_OPTIONS)
        )
    {
    case 1:
        writeMatrixToFile(matrix, rows, cols, filename);
        break;
    case 2:
        writeMatrixToBinFile(matrix, rows, cols, filenameBin);
        break;
    case 3:
        exit(0);
        break;
    }

    printf("\n");

    return 0;
}