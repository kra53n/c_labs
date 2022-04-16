#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Задания:
 * 3. Определить, сколько слов в тексте начинается на букву К или к
 * 12. Найти все прописные русские гласные буквы, которые содержатся в заданном тексте
 * 21. Даны две строки. Удалить в первой строке первое вхождение второй строки
 */

const int STRINGLEN = 100;
const char VOWELS[] = "AEIOUWYaeiouwy";
const int VOWELS_NUM = strlen(VOWELS);

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

int getSymbolNumInString(char str[STRINGLEN], char symbol)
{
	int num = 0;
    if (str[0] == symbol) num++;
    for (char*strptr = strchr(str+1, symbol); strptr != NULL; strptr = strchr(strptr+1, symbol))
        if (strptr[-1] == ' ') num++;
	return num;
}

void printStringVowels(char str[STRINGLEN])
{
	char vowels[15];
	strcpy(vowels, (char*)VOWELS);

	int slen = strlen(str);
	for (int i = 0; i < slen; i++)
		for (int j = 0; j < VOWELS_NUM; j++)
			if (VOWELS[j] == str[i]) vowels[j] = 0;

	printf("Vowels in a string: ");
	for (int i = 0; i < VOWELS_NUM; i++)
		if (!vowels[i])
			printf("%c", VOWELS[i]);
    printf("\n");
}

void delFirstOccurenceInString(char dst[STRINGLEN], char occur[STRINGLEN])
{
    int lenOccur = strlen(occur) - 1;
    for (char* dstptr = strchr(dst, *occur); dstptr != NULL; dstptr = strchr(dstptr+1, *occur))
    {
        if (!strncmp(dstptr, occur, lenOccur))
        {
            char res[STRINGLEN];
            strncpy(res, dst, abs(dst - dstptr) / sizeof(char));
            strcat(res, dst+lenOccur+1);
            dst = res;
	printf("\nString: %s", res);
        }
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
		printf("Number of k and K: %d\n", getSymbolNumInString(str, 'k') +
			getSymbolNumInString(str, 'K'));
		break;
	case 2:
		printStringVowels(str);
		break;
	case 3:
		printStringWithDeletedOccurence(str);
		break;
	}

	return 0;
}
