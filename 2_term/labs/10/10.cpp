#include <stdio.h>
#include <stdlib.h>

/* Задания:
 * 3. Определить, сколько слов в тексте начинается на букву К или к
 * 12. Найти все прописные русские гласные буквы, которые содержатся в заданном тексте
 * 21. Даны две строки. Удалить в первой строке первое вхождение второй строки
 */

const int STRINGLEN = 100;
const char VOWELS[] = "AEIOUWYaeiouwy";

void fillString(const char title[STRINGLEN], char str[STRINGLEN])
{
	printf("%s", title); gets_s(str, STRINGLEN);
}

int askUserAboutTask()
{
	int choice;
	bool cond;
	do {
		printf("\nChoose task:\n");
		printf("\t1. Find num of words with started K and k\n");
		printf("\t2. Find all vowels letters int string\n");
		printf("\t3. Delete occurrence of the second string in the first string\n");
		printf("\nChoose: "); scanf_s("%d%*c", &choice);

		cond = choice < 1 || choice > 3;
		if (cond)
			printf("You could write a number from 1 to 3. Try again!\n");
	} while (cond);

	return choice;
}

int getSymbolsNumInString(char str[STRINGLEN], char symbol)
{
	int num = 0;
	if (str[0] == symbol) num++;
	for (int i = 1; str[i] != 0; i++)
		if (str[i] == symbol && str[i - 1] == ' ') num++;

	return num;
}

void copyString(char dst[STRINGLEN], char src[STRINGLEN])
{
	int i = 0;
	for (; src[i] != 0; i++) dst[i] = VOWELS[i];
	dst[i] = 0;
}

int strLen(char str[STRINGLEN])
{
	int len;
	for (len = 0; str[len] != 0; len++);
	return len;
}

void printVowelsInString(char str[STRINGLEN])
{
	char vowels[15];
	copyString(vowels, (char*)VOWELS);

	for (int i = 0; str[i] != 0; i++)
		for (int j = 0; VOWELS[j] != 0; j++)
			if (VOWELS[j] == str[i]) vowels[j] = '\n';

	printf("Vowels in a string: ");
	for (int i = 0; vowels[i] != 0; i++)
		if (vowels[i] == '\n')
			printf("%c", VOWELS[i]);
}

void findOccurenceIndexes(char dst[STRINGLEN], char occur[STRINGLEN], int& startidx, int& endidx)
{
	for (int i = 0; dst[i] != 0; i++)
	{
		bool flag = true;
		endidx = i;
		for (int j = 0; occur[j] != 0; j++)
		{
			if (dst[endidx++] != occur[j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
		{
			startidx = i;
			break;
		}
	}
}

void delFirstOccurenceInString(char dst[STRINGLEN], char occur[STRINGLEN])
{
	int startidx = -1, endidx = 0;
	findOccurenceIndexes(dst, occur, startidx, endidx);

	if (startidx != -1)
	{
		int dstLen = strLen(dst) + 1;
		for (int i = startidx, j = endidx; j < dstLen; i++, j++)
			dst[i] = dst[j];
	}
}

void printStringWithDeletedOccurence(char str[STRINGLEN])
{
	char occur[STRINGLEN];
	fillString("Write a occurenece string: ", occur);
	delFirstOccurenceInString(str, occur);
	printf("\nString: %s", str);
}

int main()
{
	system("chcp 1251"); system("cls");
	
	char str[STRINGLEN];
	fillString("Write a string: ", str);

	switch (askUserAboutTask())
	{
	case 1:
		printf("Number of k and K: %d", getSymbolsNumInString(str, 'k') +
			getSymbolsNumInString(str, 'K'));
		break;
	case 2:
		printVowelsInString(str);
		break;
	case 3:
		printStringWithDeletedOccurence(str);
		break;
	}

	return 0;
}
