#pragma once

struct Element
{
	int data;
	Element* next;
};

struct Queue
{
	Element* head = NULL;
	Element* tail = NULL;
};

void QueueClear(Queue& q);

void QueuePush(Queue& q, int d);
int QueuePull(Queue& q);
int QueuePeek(const Queue& q);
bool QueueIsEmpty(const Queue& q);

void QueuePrint(const Queue& q);