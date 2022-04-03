#ifndef DYNARRAY_H
#define DYNARRAY_H

int askUserAboutNumber(char const title[]);
int askUserAboutRow(int arrSize);

float** mallocArray2D(int rows=0);
float** reallocArray2D(float** arr, int num);
void freeArray(float** arr);

int getArray2DSize(float** arr);
void mallocArray2DForArray(float** arr, int row, int cols);
float** getFilledArrayManually();

void printArray2D(float** arr);

float** getArrayFromFile(char filename[]);
errno_t writeArrayToFile(float** arr, char filename[]);

float** getArrayFromBinFile(char filename[]);
errno_t writeArrayToBinFile(float** arr, char filename[]);

float** getArray2DWithAddedRow(float** arr, int row, int cols);
float** getArray2DWithDeletedRow(float** arr, int row);

#endif
