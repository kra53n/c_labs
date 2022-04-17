#include <stdio.h>
#include "stack.h"

int stackProduct(Stack* s)
{
	int product = 1;
	for (int i = 0; i < s->len; i++)
		product *= (int)s->elems[i];
	return (int)product;
}

int stackSum(Stack* s)
{
	int sum = 0;
	for (int i = 0; i < s->len; i++)
		sum += (int)s->elems[i];
	return (int)sum;
}

int main()
{
	Stack s;
	StackInit(&s);

	printf("Write a number: ");
	for (char digit = getchar(); digit != '\n'; digit = getchar())
		StackPush(&s, digit - 48);

	printf("\nStack:\n");
	StackPrint(&s);
	printf("\nStack product: %d\nStack sum: %d\n", stackProduct(&s), stackSum(&s));
	
	StackDestroy(&s);
	return 0;
}