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
        "матрица n*m",
        "свободный массив",
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

int **initMatrix(int **arr, int &rows, int &cols)
{
    rows = askUserAboutNumber("Введите количество строк");
    cols = askUserAboutNumber("Введите количество столбцов");
    printf("\n");
    
    arr = (int **)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++)
    {
        arr[i] = (int *)malloc(cols * sizeof(int));

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

    arr = (int **)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++)
    {
        cols[i] = askUserAboutNumber("Введите количество столбцов");
        arr[i] = (int *)malloc(cols[i] * sizeof(int));
        printf("\n");

        for (int j = 0; j < cols[i]; j++)
        {
            printf("arr[%2d][%2d] = ", i+1, j+1); scanf("%d", &arr[i][j]);
        }
    }

    return arr;
}

void printMatrix(int **arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
            printf("%5d ", arr[i][j]);
        printf("\n");
    }
}

void printFreeMatrix(int **arr, int rows, int cols[])
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols[i]; j++)
            printf("%5d ", arr[i][j]);
        printf("\n");
    }
}

int findMin(int arr[], int size)
{
    int min = arr[0];
    for (int i = 0; i < size; i++)
        min = min < arr[i] ? min : arr[i];
    return min;
}

int findMax(int arr[], int size)
{
    int max = arr[0];
    for (int i = 0; i < size; i++)
        max = max > arr[i] ? max : arr[i];
    return max;
}

void printDifferenceBetweenMaxAndMinInRowsForMatrix(int **arr, int rows, int cols)
{
    for (int i = 0; i < rows; i++)
    {
        printf("Разница между максимальным и минимальным элементами в %d строке: %d\n",
            i+1, findMax(arr[i], cols) - findMin(arr[i], cols));
    }
}

void printDifferenceBetweenMaxAndMinInRowsForFreeMatrix(int **arr, int rows, int *cols)
{
    for (int i = 0; i < rows; i++)
    {
        printf("Разница между максимальным и минимальным элементами в %d строке: %d\n",
            i+1, findMax(arr[i], cols[i]) - findMin(arr[i], cols[i]));
    }
}

int main()
{
    int **arr, rows, cols, *cols_arr;

    switch (askUserAboutInitMatrixMethod())
    {
        case 1:
            arr = initMatrix(arr, rows, cols);
            printf("\n");
            printMatrix(arr, rows, cols);
            printf("\n");
            printDifferenceBetweenMaxAndMinInRowsForMatrix(arr, rows, cols);
            break;
        case 2:
            arr = initFreeMatrix(arr, rows, cols_arr);
            printf("\n");
            printFreeMatrix(arr, rows, cols_arr);
            printf("\n");
            printDifferenceBetweenMaxAndMinInRowsForFreeMatrix(arr, rows, cols_arr);
            break;
        case 3:
            exit(0);
            break;
    }

    printf("\n");
    return 0;
}
