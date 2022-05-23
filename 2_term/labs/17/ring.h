#pragma once

struct Element
{
	Element* prev;
	Element* next;
	int data;
};

struct Ring
{
	int size = 0;
	Element* currentElem = 0;
};

void RingClear(Ring& ring);
void RingPrint(Ring& ring);

void RingPrev(Ring& ring);
void RingNext(Ring& ring);

void RingPush(Ring& ring, int d);
int RingPop(Ring& ring);	
int RingPeek(const Ring& ring);