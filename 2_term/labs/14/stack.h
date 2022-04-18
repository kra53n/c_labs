#pragma once

struct Elem
{
	double value;
	Elem* next;
};

struct Stack
{
	Elem* top;
};

void StackInit(Stack* s);
void StackDestroy(Stack* s);

int StackPush(Stack* s, double value);
double StackPop(Stack* s);
double StackPeek(const Stack* s);
void StackClear(Stack* s);

bool StackIsEmpty(const Stack* s);

void StackPrint(const Stack* s);
