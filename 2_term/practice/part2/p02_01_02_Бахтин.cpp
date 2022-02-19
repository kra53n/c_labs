#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int const MAX_STRING_LEN_OPTIONS = 50;
int const MAX_LEN_ARRAY = 100;

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

    return option - offset;
}

int scanArrSize(int &size, int sizeMax, const char arrName[])
{
	do {
		printf("Введите количество %s [0;%d]: ", arrName, sizeMax);
		scanf_s("%d", &size);
	} while (size < 0 || size > sizeMax);
	return size;
}

void scanMatrixSize(int &rows, int &cols)
{
    scanArrSize(rows, MAX_LEN_ARRAY, "рядов");
    scanArrSize(cols, MAX_LEN_ARRAY, "столбцов");
}

void fillMatrixRandomly(int matrix[MAX_LEN_ARRAY][MAX_LEN_ARRAY], int rows, int cols, int start=0, int end=10)
{
	srand(time(0));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = rand() % (end - start + 1) + start;
}

errno_t fillMatrixFromFile(int matrix[MAX_LEN_ARRAY][MAX_LEN_ARRAY], int &rows, int &cols, char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "r")) return 1;

	fscanf_s(f, "%d %d\n", &rows, &cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fscanf_s(f, "%5d ", &matrix[i][j]);
		fscanf_s(f, "\n");
	}

	fclose(f);
	return 0;
}

errno_t fillMatrixFromBinFile(int matrix[MAX_LEN_ARRAY][MAX_LEN_ARRAY], int &rows, int &cols, char filename[])
{
    FILE* f;
    if (fopen_s(&f, filename, "rb")) return 1;

    fread(&rows, sizeof(int), 1, f);
    fread(&cols, sizeof(int), 1, f);

    for (int i = 0; i < rows; i++)
        fread(&matrix[i], sizeof(int), cols, f);

    return 0;
}

void outputMatrixToScreen(int matrix[MAX_LEN_ARRAY][MAX_LEN_ARRAY], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%5d\t", matrix[i][j]);
		}
		printf("\n");
	}
}

errno_t writeMatrixToFile(int matrix[MAX_LEN_ARRAY][MAX_LEN_ARRAY], int rows, int cols, char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "w")) return 1;
	
	fprintf_s(f, "%d %d\n", rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fprintf_s(f, "%5d ", matrix[i][j]);
		fprintf_s(f, "\n");
	}

	return 0;
}

errno_t writeMatrixToBinFile(int matrix[MAX_LEN_ARRAY][MAX_LEN_ARRAY], int rows, int cols, char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "wb")) return 1;

	fwrite(&rows, sizeof(int), 1, f);
	fwrite(&cols, sizeof(int), 1, f);

	for (int i = 0; i < rows; i++)
		fwrite(&matrix[i], sizeof(int), cols, f);

	return 0;
}

int numOfColsWithZero(int matrix[MAX_LEN_ARRAY][MAX_LEN_ARRAY], int rows, int cols)
{
    int num = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[j][i] == 0)
            {
                num += 1;
                break;
            }
        }
    }
    return num;
}

void numOfRowsLessThenNum(int matrix[MAX_LEN_ARRAY][MAX_LEN_ARRAY], int rows, int cols, int num, int &count)
{
    for (int i = 0; i < rows; i++)
    {
        int sum = 0;
        for (int j = 0; j < cols; j++)
        {
            sum += matrix[i][j];
        }
        if (sum / cols < num) count++;
    }
}

int main()
{
    int matrix[MAX_LEN_ARRAY][MAX_LEN_ARRAY];
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
        case 0:
            fillMatrixFromFile(matrix, rows, cols, filename);
            break;
        case 1:
            fillMatrixFromBinFile(matrix, rows, cols, filenameBin);
            break;
        case 2:
            scanMatrixSize(rows, cols);
            fillMatrixRandomly(matrix, rows, cols);
            break;
        case 3:
            exit(0);
            break;
    }

    printf("\nМатрица:\n");
    outputMatrixToScreen(matrix, rows, cols);

    printf("\nКоличество столбцов с 0 элементом: %d",
        numOfColsWithZero(matrix, rows, cols));

    int count;
    numOfRowsLessThenNum(matrix, rows, cols, 5, count);
    printf("\nКоличество строк меньше, чем число %d: %d.\n\n", 5, count);

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
        case 0:
            writeMatrixToFile(matrix, rows, cols, filename);
            break;
        case 1:
            writeMatrixToBinFile(matrix, rows, cols, filenameBin);
            break;
    }

    return 0;
}
