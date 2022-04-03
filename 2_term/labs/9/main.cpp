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

int askUserAboutActionOnArray(int &len)
{
    char options[][MAX_STRING_LEN_OPTIONS] = {
    "создать массив",
    "вывести на экран",
    "добавить строку",
    "удалить строку",
    "сохранить",
    "выход",
    };
    len = sizeof(options) / MAX_STRING_LEN_OPTIONS;
    return askUserOptions("Выберите действие:",
        options, len);
}

void clearScreen()
{
    system("cls");
}

int main()
{
    float** arr = mallocArray2D();
    int arrSize;

    char filename[] = "im_file.txt";
    char filenameBin[] = "im_file.bin";

    int action, actionsQuantity;
    do {
        action = askUserAboutActionOnArray(actionsQuantity);
        clearScreen();

        switch (action)
        {
        case 1:
            switch (askUserAboutFillingArray())
            {
            case 1:
                arr = getFilledArrayManually();
                break;
            case 2:
                arr = getArrayFromFile(filename);
                break;
            case 3:
                arr = getArrayFromBinFile(filenameBin);
                break;
            }
            break;
        case 2:
            printArray2D(arr);
            break;
        case 3:
            arrSize = getArray2DSize(arr);
            if (!arrSize)
            {
                printf("Невозможно выполнить операцию, так как размер массива равен 0!\n");
                continue;
            }
            arr = getArray2DWithAddedRow(arr, askUserAboutRow(arrSize+1),
                askUserAboutNumber("Количество элементов"));
            break;
        case 4:
            arrSize = getArray2DSize(arr);
            if (!arrSize)
            {
                printf("Невозможно выполнить операцию, так как размер массива равен 0!\n");
                continue;
            }
            arr = getArray2DWithDeletedRow(arr, askUserAboutRow(arrSize));
            break;
        case 5:
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
    } while (action != actionsQuantity);

    freeArray(arr);

    return 0;
}
