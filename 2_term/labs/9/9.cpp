#include "dynamic_array.h"

int main()
{
    float** arr = NULL;
    arr = mallocArray2D(arr);

    char filename[] = "im_file.txt";
    char filenameBin[] = "im_file.bin";

    int rows = 0;
    switch (askUserAboutFillingArray())
    {
    case 1:
        printf("Введите количество строк массива: "); scanf_s("%d", &rows);
        arr = reallocArray2D(arr, rows);
        fillArrayManually(arr);
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
    
    printArray2D(arr);

    switch (askUserAboutWritingArray())
    {
    case 1:
        writeArrayToFile(arr, filename);
        break;
    case 2:
        writeArrayToBinFile(arr, filenameBin);
        break;
    }
    
    freeArray(arr);
    
    return 0;
}
