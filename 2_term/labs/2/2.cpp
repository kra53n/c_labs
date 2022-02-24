#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* Задание:
 * вычислить сумму наибольшего и наименьшего элементов для каждой строки */

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

int askUserAboutInitMatrixMethod()
{
    char options[][MAX_STRING_LEN_OPTIONS] = {
        "массив",
        "матрица",
        "выход",
    };
    return askUserOptions("Выберите способ инициализации матрицы:", 
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

int** mallocMatrix(int rows, int cols)
{
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++)
        matrix[i] = (int*)malloc(cols * sizeof(int));
    return matrix;
}

void fillArrayManually(int *arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            printf("arr[%2d][%2d] = ", i+1, j+1);
            scanf("%d", (arr + i*cols + j));
        }
}

void fillMatrixManually(int** matrix, int rows, int cols)
{
    printf("Error");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            printf("arr[%2d][%2d] = ", i+1, j+1);
            scanf("%d", &matrix[i][j]);
    printf("Error");
        }
}

void printArray(int *arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%5d ", *(arr + i*rows + j));
        printf("\n");
    }
}

void printMatrix(int **matrix, int rows, int cols)
{
    printf("Error");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%5d ", matrix[i][j]);
        printf("\n");
    }
}

void freeMatrix(int** matrix, int rows)
{
    for (int i = 0; i < rows; i++)
        free(matrix[i]);
    free(matrix);
}

int findMin(int* arr, int size)
{
    int min = arr[0];
    for (int i = 0; i < size; i++)
        min = min < arr[i] ? min : arr[i];
    return min;
}

int findMax(int* arr, int size)
{
    int max = arr[0];
    for (int i = 0; i < size; i++)
        max = max > arr[i] ? max : arr[i];
    return max;
}

void printDifferenceBetweenMaxAndMinInRowsForArray(int* arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        printf("Разница между максимальным и минимальным элементами в %d строке: %d\n",
            i+1, findMax(arr + i*cols, cols) - findMin(arr + i*cols, cols));
    }
}

void printDifferenceBetweenMaxAndMinInRowsForMatrix(int** arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        printf("Разница между максимальным и минимальным элементами в %d строке: %d\n",
            i+1, findMax(arr[i], cols) - findMin(arr[i], cols));
    }
}

int main()
{
    int **arr;

    int userChoice = askUserAboutInitMatrixMethod();

    int rows = askUserAboutNumber("Введите количество строк");
    int cols = askUserAboutNumber("Введите количество столбцов");

    switch (userChoice)
    {
        case 1:
        {
            int *arr = (int*)malloc(rows * cols * sizeof(int));

            fillArrayManually(arr, rows, cols);
            printArray(arr, rows, cols);
            printDifferenceBetweenMaxAndMinInRowsForArray(arr, rows, cols);
            free(arr);
            break;
        }
        case 2:
        {
            int** matrix = mallocMatrix(rows, cols);

            fillMatrixManually(matrix, rows, cols);
            printMatrix(arr, rows, cols);
            printDifferenceBetweenMaxAndMinInRowsForMatrix(arr, rows, cols);
            freeMatrix(matrix, rows);
            break;
        }
        case 3:
            exit(0);
            break;
    }

    printf("\n");
    return 0;
}
