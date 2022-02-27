#include <stdio.h>

void scanStr(char str[])
{
    printf("Введите строку: "); scanf("%[^\n]%*c", str);
}

void insertingSpacesInStrCenter()
{
    char str[100];
    char resstr[100];
    scanStr(str);

    int i, j;
    int numspaces = 0;
    for (i = j = 0; str[i] != 0; i++)
    {
        if (str[i] != ' ')
            resstr[j++] = str[i];
        else
            numspaces++;
    }
    resstr[j] = '\0';

    while (i > j/2)
        resstr[i--] = resstr[i-numspaces];
    while (i - j/2 < numspaces)
        resstr[i++] = ' ';
    
    printf("%s\n", resstr, j);
}

int main()
{
    insertingSpacesInStrCenter();
    return 0;
}
