#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* Система:
*    i + j, i > j
*    i * j, i <= j
* 
*  Вычислить среднее арифметическое элементов столбца, в котором находится минимальный элемент матрицы
*/

const int MAX = 100;

int scanArrSize(int sizeMax, const char arrName[])
{
	int size;
	do {
		printf("Введите количество %s [0;%d]: ", arrName, sizeMax);
		scanf_s("%d", &size);
	} while (size < 0 || size > sizeMax);
	return size;
}

void fillMatrixManually(float matrix[MAX][MAX], int rows, int cols, int offset=0)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
		{
			printf("matrix[%2d][%2d] = ", i+offset, j+offset);
			scanf_s("%f", &matrix[i][j]);
		}
}

void fillMatrixRandomly(float matrix[MAX][MAX], int rows, int cols)
{
	srand(time(0));
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			matrix[i][j] = rand() % 10000 / 100.;
}

void fillMatrixUsingFormula(float matrix[MAX][MAX], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			if (i > j)
				matrix[i][j] = i + j;
			else
				matrix[i][j] = i * j;
}

errno_t fillMatrixFromFile(float matrix[MAX][MAX], int& rows, int& cols, char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "r")) return 1;

	fscanf_s(f, "%d %d\n", &rows, &cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fscanf_s(f, "%5.2f ", &matrix[i][j]);
		fscanf_s(f, "\n");
	}

	fclose(f);
	return 0;
}

errno_t fillMatrixFromBinFile(float matrix[MAX][MAX], int& rows, int& cols, char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "rb")) return 1;

	fread(&rows, sizeof(int), 1, f);
	fread(&cols, sizeof(int), 1, f);

	for (int i = 0; i < rows; i++)
		fread(&matrix[i], sizeof(float), cols, f);

	return 0;
}

void outputMatrixToScreen(float matrix[MAX][MAX], int rows, int cols)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("%5.2f\t", matrix[i][j]);
		}
		printf("\n");
	}
}

errno_t writeMatrixToFile(float matrix[MAX][MAX], int rows, int cols, char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "w")) return 1;
	
	fprintf_s(f, "%d %d\n", rows, cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
			fprintf_s(f, "%5.2f ", matrix[i][j]);
		fprintf_s(f, "\n");
	}

	return 0;
}

errno_t writeMatrixToBinFile(float matrix[MAX][MAX], int rows, int cols, char filename[])
{
	FILE* f;
	if (fopen_s(&f, filename, "wb")) return 1;

	fwrite(&rows, sizeof(int), 1, f);
	fwrite(&cols, sizeof(int), 1, f);

	for (int i = 0; i < rows; i++)
		fwrite(&matrix[i], sizeof(float), cols, f);

	return 0;
}

int askUserScanOption()
{
	int choice;
	do
	{
		printf("\nВведите способ записи:\n");
		printf("\t1) вручную\n");
		printf("\t2) рандомно\n");
		printf("\t3) формулой\n");
		printf("\t4) из файла\n");
		printf("\t5) из бинарного файла\n");
		printf("Выбор: ");  scanf_s("%d", &choice);
	} while (choice < 1 || choice > 5);
	return choice;
}

int askUserPrintOption()
{
	int choice;
	do
	{
		printf("\nВведите способ вывода:\n");
		printf("\t1) в консоль\n");
		printf("\t2) в файл\n");
		printf("\t3) в бинарный файла\n");
		printf("Выбор: "); scanf_s("%d", &choice);
	} while (choice < 1 || choice > 3);
	return choice;
}

int colWithMinNumInMatrix(float matrix[MAX][MAX], int rows, int cols)
{
	int row = 0, col = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 1; j < cols; j++)
		{
			if (matrix[row][col] > matrix[i][j])
			{
				row = i;
				col = j;
			}
		}
	return col;
}

float arithmeticMeanOfColWithMinElemOfMatrix(float matrix[MAX][MAX], int rows, int col)
{
	float sum = 0;
	for (int i = 0; i < rows; i++)
		sum += matrix[i][col];
	return sum / rows;
}

int main()
{
	float matrix[MAX][MAX];
	int cols, rows;

	char filename[] = "im_file.txt";
	char filenameBin[] = "im_file.bin";

	switch (askUserScanOption())
	{
	case 1:
		rows = scanArrSize(MAX, "рядов");
		cols = scanArrSize(MAX, "столбцов");
		fillMatrixManually(matrix, rows, cols, 1);
		break;
	case 2:
		rows = scanArrSize(MAX, "рядов");
		cols = scanArrSize(MAX, "столбцов");
		fillMatrixRandomly(matrix, rows, cols);
		break;
	case 3:
		rows = scanArrSize(MAX, "рядов");
		cols = scanArrSize(MAX, "столбцов");
		fillMatrixUsingFormula(matrix, rows, cols);
		break;
	case 4:
		fillMatrixFromFile(matrix, rows, cols, filename);
		break;
	case 5:
		fillMatrixFromBinFile(matrix, rows, cols, filenameBin);
		break;
	}

	switch (askUserPrintOption())
	{
	case 1:
		outputMatrixToScreen(matrix, rows, cols);
		break;
	case 2:
		writeMatrixToFile(matrix, rows, cols, filename);
		break;
	case 3:
		writeMatrixToBinFile(matrix, rows, cols, filenameBin);
		break;
	}

	printf("\nСреднее арифметическое столбца, содержащий минимальным элемент матрицы: %f\n",
		arithmeticMeanOfColWithMinElemOfMatrix(matrix, rows, colWithMinNumInMatrix(matrix, rows, cols)));

	return 0;
}