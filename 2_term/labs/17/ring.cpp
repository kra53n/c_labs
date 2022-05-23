#include <stdio.h>
#include <malloc.h>
#include "ring.h"

void RingClear(Ring& ring)
{
	Element* elem;
	for (int i = 0; i < ring.size; i++)
	{
		elem = ring.currentElem;
		ring.currentElem->prev = ring.currentElem->next;
		if (ring.currentElem->next == ring.currentElem->prev)
		{
			ring.currentElem = NULL;
		}
		free(elem);
	}
	ring.size = 0;
}

void RingPrint(Ring& ring)
{
	for (int i = 1; i <= ring.size; i++)
	{
		printf("[%d] %d\n", i, ring.currentElem->data);
		RingNext(ring);
	}
}

void RingPrev(Ring& ring)
{
	if (ring.currentElem != NULL)
	{
		ring.currentElem = ring.currentElem->prev;
	}
}

void RingNext(Ring& ring)
{
	if (ring.currentElem != NULL)
	{
		ring.currentElem = ring.currentElem->next;
	}
}

void RingPush(Ring& ring, int d)
{
	Element* elem = (Element*)malloc(sizeof(Element));
	elem->data = d;

	if (ring.currentElem == NULL)
	{
		elem->prev = elem;
		elem->next = elem;
		ring.currentElem = elem;
	}
	else
	{
		elem->prev = ring.currentElem;
		elem->next = ring.currentElem->next;
		ring.currentElem->next = elem;
	}
	ring.size++;
}

int RingPop(Ring& ring)
{
	Element* elem = ring.currentElem;
	ring.size--;
	ring.currentElem->prev = ring.currentElem->next;

	ring.currentElem;

	if (!ring.size && ring.currentElem->next == ring.currentElem->prev)
	{
		ring.currentElem = NULL;
		ring.size = 0;
	}

	int d = elem->data;
	free(elem);
	return d;
}

int RingPeek(const Ring& ring);