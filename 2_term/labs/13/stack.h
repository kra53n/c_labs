#pragma once

struct Stack
{
	double* elems;
	int len;
	int top;
};

void StackInit(Stack* s, int len=0);
void StackDestroy(Stack* s);

void StackPush(Stack* s, double value);
double StackPop(Stack* s);
double StackPeek(Stack* const s);
void StackClear(Stack* s);
int StackIsEmpty(Stack* s);

void StackPrint(Stack* const s);