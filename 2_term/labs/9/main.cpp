#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"

const int MAX_STRING_LEN_OPTIONS = 100;

int askUserOptions(
    char const title[],
    char options_names[][MAX_STRING_LEN_OPTIONS],
    int elems_num,
    int offset = 1
)
{
    int option, cond;

    do {
        printf("%s\n", title);
        for (int i = 0; i < elems_num; i++)
            printf("\t%d) %s\n", i + offset, options_names[i]);
        printf("\nВвод: "); scanf_s("%d", &option);

        cond = offset > option || option > elems_num + offset;
        if (cond)
            printf("\nВведено неверное число! Попробуйте снова.\n");
    } while (cond);

    return option;
}

int askUserAboutFillingArray()
{
    char options[][MAX_STRING_LEN_OPTIONS] = {
        "создать массив, заполнив вручную",
        "загрузить массив из текстового файла",
        "загрузить массив из бинарного файла",
        "выход",
    };
    return askUserOptions("Выберите способ заполнения массива:",
        options, sizeof(options) / MAX_STRING_LEN_OPTIONS);
}

int askUserAboutWritingArray()
{
    char options[][MAX_STRING_LEN_OPTIONS] = {
        "сохранить массив в текстовый файл",
        "сохранить массив в бинарный файл",
        "выход",
    };
    return askUserOptions("Выберите способ заполнения массива:",
        options, sizeof(options) / MAX_STRING_LEN_OPTIONS);
}

int askUserAboutArrayAction()
{
    char options[][MAX_STRING_LEN_OPTIONS] = {
    "вывести на экран",
    "добавить строку",
    "удалить строку",
    "сохранить",
    "выход",
    };
    return askUserOptions("Выберите действие:",
        options, sizeof(options) / MAX_STRING_LEN_OPTIONS);
}

void clearScreen()
{
    system("cls");
}

int main()
{
    float** arr = mallocArray2D();

    char filename[] = "im_file.txt";
    char filenameBin[] = "im_file.bin";

    int rows = 0;
    switch (askUserAboutFillingArray())
    {
    case 1:
        arr = getFilledArrayManually(arr);
        break;
    case 2:
        arr = getArrayFromFile(arr, filename);
        break;
    case 3:
        arr = getArrayFromBinFile(arr, filenameBin);
        break;
    case 4:
        exit(0);
        break;
    }

    int action;
    do {
        action = askUserAboutArrayAction();
        clearScreen();

        switch (action)
        {
        case 1:
            printArray2D(arr);
            break;
        case 2:
            // add a row
            break;
        case 3:
            // del a row
            break;
        case 4:
            switch (askUserAboutWritingArray())
            {
            case 1:
                writeArrayToFile(arr, filename);
                break;
            case 2:
                writeArrayToBinFile(arr, filenameBin);
                break;
            }
            break;
        }
    } while (action != 5);

    printArray2D(arr);

    int row = getArray2DSize(arr);
    printf("\nrow: %d", row);
    row = 2;
    arr = getArray2DWithAddedRow(arr, row, 1);
    arr[row][0] = 7;
    row++;
    arr = getArray2DWithAddedRow(arr, row, 1);
    arr[row][0] = 7;
    printArray2D(arr);

    arr = getArray2DWithDeletedRow(arr, 0);
    printArray2D(arr);

    //freeArray(arr);

    return 0;
}
