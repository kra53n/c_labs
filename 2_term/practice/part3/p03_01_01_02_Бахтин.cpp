#include <stdio.h>
#include <malloc.h>

int countSymbol(char* string, char symbol)
{
    int num = 0;
    for (int i = 0; string[i] != 0; i++)
        if (string[i] == symbol)
            num += 1;
    return num;
}

int strLen(char* string)
{
    int num = 0;
    for (int i = 0; string[i] != 0; i++)
        num += 1;
    return num;
}

char* removeSymbolInString(char* string, char symbol)
{
    char* resString = (char*)malloc(sizeof(char));
    int j;
    for (int i = j = 0; string[i] != 0; i++)
        if (string[i] != symbol)
        {
            resString = (char*)realloc(resString, (j + 1) * sizeof(char));
            resString[j++] = string[i];
        }
    resString[j] = '\0';
    return resString;
}

char* genereteStrOfSymbols(int num, char symbol)
{
    char* str = (char*)malloc(sizeof(char));
    int i = 0;
    while (i < num)
    {
        str = (char*)realloc(str, (i+1) * sizeof(char));
        str[i++] = symbol;
    }
    str[i] = '\0';
    return str;
}

void strCpy(char* str1, char* str2)
{
    int str1Len = strLen(str1);
    int i = 0;
    while (str2[i] != 0)
    {
        str1 = (char*)realloc(str1, (str1Len + i + 1) * sizeof(char));
        str1[str1Len + i++] = str2[i];
    }
    str1[str1Len + i] = '\0';
}

int main()
{
	char testString[] = "  хаха  so niiiiiceeeee      eeeeeee";
    char* newString = removeSymbolInString(testString, ' ');
    int numSpaces = countSymbol(testString, ' ');

    printf("\n%s. Num of spaces: %d\n", newString, numSpaces);

    strCpy(newString, "I'm string");
    strCpy(newString, "I'm string");
    strCpy(newString, genereteStrOfSymbols(numSpaces, '1'));

    printf("\n%s. Num of spaces: %d\n", genereteStrOfSymbols(numSpaces, ' '), numSpaces);
    printf("\n%s. Num of spaces: %d\n", newString, numSpaces);

	return 0;
}
