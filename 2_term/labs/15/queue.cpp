#include <malloc.h>
#include <stdio.h>

#include "queue.h"

void QueueClear(Queue& q)
{
	for (Element* cur = q.head; cur != NULL;)
	{
		Element* elem = cur;
		cur = elem->next;
		free(elem);
	}

	q.head;

	q.head = NULL;
}

void QueuePush(Queue& q, int d)
{
	Element* elem = (Element*)malloc(sizeof(Element));
	if (elem)
	{
		elem->data = d;
		elem->next = NULL;
		
		if (q.head != NULL)
		{
			q.tail->next = elem;
			q.tail = elem;
		}
		else
		{
			q.head = elem;
			q.tail = elem;
		}
	}
}

int QueuePull(Queue& q)
{
	if (q.head == NULL)
	{
		return 0;
	}
	
	int d = q.head->data;

	if (q.head == q.tail)
	{
		q.tail = NULL;
	}

	Element* elem = q.head;
	q.head = q.head->next;
	free(elem);
	
	return d;
}

int QueuePeek(const Queue& q)
{
	if (q.head == NULL)
	{
		return 0;
	}
	int d = q.head->data;
	return d;
}

bool QueueIsEmpty(const Queue& q)
{
	return q.head == NULL;
}

void QueuePrint(const Queue& q)
{
	int i = 1;
	for (Element* cur = q.head; cur != NULL; cur = cur->next, i++)
	{
		printf("[%d] %d\n", i, cur->data);
	}
}