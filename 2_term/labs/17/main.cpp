#include <stdio.h>
#include "ring.h"

int main()
{
	Ring ring;

	RingPush(ring, 1);
	RingPush(ring, 2);
	RingPush(ring, 3);
	RingPush(ring, 4);
	RingPush(ring, 5);

	RingPrint(ring);
	int d = RingPop(ring);

	printf("\nElement: %d\n", d);

	ring;

	RingPrint(ring);

	return 0;
}