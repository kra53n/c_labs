#ifndef DYNARRAY_H
#define DYNARRAY_H

int askUserAboutNumber(char const title[]);
int askUserAboutRow(int arrSize);

float** mallocArray2D(int rows=0);
float** reallocArray2D(float** arr, int num);
void freeArray2D(float** arr);

int getArray2DSize(float** arr);
void mallocArrayForArray2D(float** arr, int row, int cols);
float** getFilledArray2DManually();

void printArray2D(float** arr);

float** getArray2D(char filename[]);
errno_t writeArray2DToFile(float** arr, char filename[]);

float** getArray2DFromBinFile(char filename[]);
errno_t writeArray2DToBinFile(float** arr, char filename[]);

float** getArray2DWithAddedRow(float** arr, int row, int cols);
float** getArray2DWithDeletedRow(float** arr, int row);

#endif
