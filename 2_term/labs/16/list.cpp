#include <malloc.h>
#include <stdio.h>
#include "list.h"

void ListClear(List& list)
{
	for (Element* cur = list.head; cur != NULL; cur = cur->next)
	{
		free(cur);
	}
	list.head = NULL;
}

int ListLen(const List& list)
{
	int len = 0;
	for (Element* cur = list.head; cur != NULL; cur = cur->next, len++);
	return len;
}

bool ListIsEmpty(const List& list)
{
	return list.head == NULL;
}

void ListPush(List& list, int d)
{
	for (Element* cur = list.head; cur != NULL; cur = cur->next)
	{
		if (cur->next == NULL || d < cur->next->data)
		{
			Element* elem = (Element*)malloc(sizeof(Element));
			elem->data = d;
			elem->next = cur->next;
			cur->next = elem;
			break;
		}
	}

	if (list.head != NULL && d < list.head->data)
	{
		Element* tmp = list.head;
		list.head = list.head->next;
		tmp->next = tmp->next->next;
		list.head->next = tmp;
	}

	if (list.head == NULL)
	{
		Element* elem = (Element*)malloc(sizeof(Element));
		elem->data = d;
		elem->next = NULL;
		list.head = elem;
	}
}

int ListPop(List& list)
{
	if (list.head == NULL) return 0;

	Element* elem;
	for (elem = list.head; elem->next != NULL; elem = elem->next);

	int d = elem->data;
	free(elem->next);
	elem->next = NULL;
	return d;
}

int ListPeek(const List& list)
{
	Element* elem;
	for (elem = list.head; elem->next != NULL; elem = elem->next);
	return elem->data;
}

void ListPrint(const List& list)
{
	int i = 1;
	for (Element* cur = list.head; cur != NULL; cur = cur->next, i++)
	{
		printf("[%d] %d\n", i, cur->data);
	}
}
