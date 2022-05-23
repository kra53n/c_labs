#include <stdio.h>

#include "queue.h"

int main()
{
	Queue queue;
	
	int num = 10;
	printf("Введите %d элементов очереди\n", num);
	for (int i = 1; i <= num; i++)
	{
		int d;
		printf("[%d]: ", i); scanf_s("%d", &d);
		QueuePush(queue, d);
	}

	printf("\nЗаполненная очередь:\n");
	QueuePrint(queue);

	for (Element* cur = queue.head; cur != NULL; cur = cur->next)
	{
		cur->data = cur->data % 2 ? cur->data : cur->data * cur->data;
	}
	printf("\nОбработанная очередь:\n");
	QueuePrint(queue);
	
	QueueClear(queue);

	return 0;
}