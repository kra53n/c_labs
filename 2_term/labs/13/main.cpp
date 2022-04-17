#include <stdio.h>
#include "stack.h"


int main()
{
	Stack s;
	StackInit(&s);

	printf("Write a number: ");
	for (char digit = getchar(); digit != '\n'; digit = getchar())
		StackPush(&s, digit - 48);
	printf("\nStack:\n");
	StackPrint(&s);

	return 0;
}
