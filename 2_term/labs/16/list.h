#pragma once

struct Element
{
	int data;
	Element* next;
};

struct List
{
	Element* head = 0;
};

void ListClear(List& list);
int ListLen(const List& list);
bool ListIsEmpty(const List& list);

void ListPush(List& list, int d);
int ListPop(List& list);
int ListPeek(const List& list);

void ListPrint(const List& list);
