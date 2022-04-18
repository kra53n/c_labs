#include <stdio.h>
#include <malloc.h>
#include <float.h>
#include "stack.h"

void StackInit(Stack* s)
{
	s->top = NULL;
}

void StackDestroy(Stack* s)
{
	StackClear(s);
}

int StackPush(Stack* s, double value)
{
	Elem* elem = (Elem*)malloc(sizeof(Elem));
	if (!elem)
		return 0;
	elem->next = s->top;
	elem->value = value;
	s->top = elem;
	return 1;
}

double StackPop(Stack* s)
{
	Elem* tmp;
	double value = DBL_MAX;

	if (s->top != NULL)
	{
		tmp = s->top;
		value = tmp->value;
		s->top = s->top->next;
		free(tmp);
	}
	return value;
}

double StackPeek(const Stack* s)
{
	if (s->top)
		return s->top->value;
}

void StackClear(Stack* s)
{
	while (!StackIsEmpty(s)) StackPop(s);
}

bool StackIsEmpty(const Stack* s)
{
	return s->top == NULL;
}

void StackPrint(const Stack* s)
{
	int i = 1;
	for (Elem* elem = s->top; elem; elem = elem->next, i++)
		printf("[%2d] %.f\n", i, elem->value);
}	
