#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

void input_key(int* a, int n)
{

	printf("input array:\n");
	for (int i = 0; i < n; i++)
	{
		printf("a[%d]=", i);
		scanf_s("%d", &a[i]);
	}
}

void print_arr(int* a, int n)
{
	for (int i = 0; i < n; i++)
		printf("%d  ", a[i]);
}

void input_rand(int* a, int n)
{

	srand(time(NULL));
	int c, b;
	do
	{
		printf("c=");
		scanf_s("%d", &c);
		printf("b=");
		scanf_s("%d", &b);
	} while (c > b);
	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % (b - c + 1) + c;
	}

	print_arr(a, n);
}

void input_file(int* a, int n)
{
	FILE* ft;
	fopen_s(&ft, "f.txt", "rt");
	fscanf_s(ft, "%d", &n);
	for (int i = 0; i < n; i++)
		fscanf_s(ft, "%d", &a[i]);
	fclose(ft);
	print_arr(a, n);
}

void output_file(int* a, int n)
{
	FILE* f;
	fopen_s(&f, "f.txt", "w+");
	fprintf(f, "%d \n", n);
	for (int i = 0; i < n; i++)
		fprintf(f, "%d\n ", a[i]);
	fclose(f);
}

int min_in_arr(int* a, int n)
{
	int min = a[0];
	for (int i = 0; i < n; i++)
		if (a[i] < min)
			min = a[i];
	return min;
}

int main()
{
	int a[100];
	int n;
	int ch;
	do
	{
		printf("n=");
		scanf_s("%d", &n);
	} while ((n < 0) || (n >= 100));
	printf("input array:\n 1-from keyboard, 2-random,3-from file");
	scanf_s("%d", &ch);
	switch (ch)
	{
	case 1:
		input_key(a, n);
		break;
	case 2:
		input_rand(a, n);
		break;
	case 3:
		input_file(a, n);
		break;
	default:
		printf("error");
		exit(1);
	}
	printf("\n min=%d", min_in_arr(a, n));
	output_file(a, n);
	return 0;
}
