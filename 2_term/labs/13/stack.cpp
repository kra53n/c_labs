#include <stdio.h>
#include <malloc.h>
#include <float.h>
#include "stack.h"

void StackInit(Stack* s, int len)
{
	if (s->elems = (double*)malloc(sizeof(double) * len))
		s->len = len;
	else
		s->len = -1;
	s->top = -1;
}

void StackDestroy(Stack* s)
{
	if (s->elems)
		free(s->elems);
	s->len = -1;
	s->top = -1;
}

void StackPush(Stack* s, double value)
{
	s->top++;
	if (s->top >= s->len - 1)
		s->elems = (double*)realloc(s->elems, sizeof(double) * (s->top + 1));
	s->elems[s->top] = value;
}

double StackPop(Stack* s)
{
	if (s->top > -1)
		return s->elems[s->top--];
	return DBL_MAX;
}

double StackPeek(Stack* const s)
{
	if (s->top > -1)
		return s->elems[s->top];
	return DBL_MAX;
}

void StackClear(Stack* s)
{
	s->top = -1;
}

int StackIsEmpty(Stack* const s)
{
	if (s->top < 0)
		return 1;
	return 0;
}

void StackPrint(Stack* s)
{
	for (int i = 0; i <= s->top; i++)
		printf("[%2d] %.0lf\n", i+1, s->elems[i]);
}