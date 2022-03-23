#include <stdio.h>

/* Пусть для каждого студента в группе, состоящей из N человек, заданы оценки
   по трем экзаменам. Определить студента с наибольшим средним баллом по
   экзаменам и вывести его оценки */

struct Student
{
	char name[40];
	int subject1;
	int subject2;
	int subject3;
};

int scanArraySize(int sizeMax)
{
	int size;
	do {
		printf("Введите количество студентов [0;100]: "); scanf_s("%d", &size);
	} while (size < 0 || size > sizeMax);
	return size;
}

void scanSubjectMark(const char s[], int &subject)
{
	int mark;
	do {
		printf("Введите оценку за #%s предмет: ", s); scanf_s("%d", &mark);
	} while (mark < 1 || mark > 5);
	subject = mark;
}

void scanStudentArrayManually(Student arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("\nВведите ФИО студента: "); scanf_s("%s", &arr[i].name, 40);
		scanSubjectMark("I", arr[i].subject1);
		scanSubjectMark("II", arr[i].subject2);
		scanSubjectMark("III", arr[i].subject3);
		printf("\n");
	}
}

void printStudentArray(Student arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("\nФио студента: %s\n", arr[i].name);
		printf("Оценка за I предмет: %d\n", arr[i].subject1);
		printf("Оценка за II предмет: %d\n", arr[i].subject2);
		printf("Оценка за III предмет: %d\n", arr[i].subject3);
	}
}

errno_t scanStudentArrayFromFile(char filename[], Student arr[], int &size)
{
	FILE* f;
	if (fopen_s(&f, filename, "r")) return 1;

	fscanf_s(f, "%d", &size);

	for (int i = 0; i < size; i++)
		fscanf_s(f, "%s %d %d %d", arr[i].name, 40,
			&arr[i].subject1, &arr[i].subject2, &arr[i].subject3);

	fclose(f);
	return 0;
}

errno_t printStudentArrayToFile(char filename[], Student arr[], int size)
{
	FILE* f;
	if (fopen_s(&f, filename, "w")) return 1;
	
	fprintf_s(f, "%d\n", size);
	for (int i = 0; i < size; i++)
		fprintf_s(f, "%s %d %d %d\n", arr[i].name,
			arr[i].subject1, arr[i].subject2, arr[i].subject3);

	fclose(f);
	return 0;
}

int askUserScanOption()
{
	int choice;
	do
	{
		printf("\nВведите способ записи:\n");
		printf("\t1) вручную\n");
		printf("\t2) из файла\n");
		printf("Выбор: ");  scanf_s("%d", &choice);
	} while (choice < 1 || choice > 2);
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
		printf("Выбор: "); scanf_s("%d", &choice);
	} while (choice < 1 || choice > 2);
	return choice;
}

int main()
{
	const int arrSizeMax = 100;
	Student arr[arrSizeMax];
	int arrSize;

	switch (askUserScanOption())
	{
	case 1:
		arrSize = scanArraySize(arrSizeMax);
		scanStudentArrayManually(arr, arrSize);
		break;
	case 2:
		char filename[] = "im_file.txt";
		scanStudentArrayFromFile(filename, arr, arrSize);
		break;
	}

	switch (askUserPrintOption())
	{
	case 1:
		printStudentArray(arr, arrSize);
		break;
	case 2:
		char filename[] = "im_file.txt";
		printStudentArrayToFile(filename, arr, arrSize);
		break;
	}

	return 0;
}