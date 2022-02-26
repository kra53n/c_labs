#include <stdio.h>

int main()
{
	char testString[] = "  хаха  ";
	char resString[100];
	char resStringSpaces[100];

	printf("%s\n", testString);

	int i, j = 0;
	int numSpaces = 0;
	for (i = 0; testString[i] != '\0'; i++)
	{
		if (testString[i] != ' ')
		{
			resString[j++] = testString[i];
			printf("\n%d %c", j, resString[j]);
		}
		else
			numSpaces++;
	}
	resString[j] = '\0';

	for (int i = j; i > j / 2; i--)
	{
		resString[i + numSpaces] = resString[i];
		printf("\n%s\n", resString);
	}
	for (int i = j / 2; i < j / 2 + numSpaces; i++)
	{
		resString[i] = ' ';
	}


	printf("%s\n", resString);

	printf("\nКоличество пробелов: %d", numSpaces);

	return 0;
}