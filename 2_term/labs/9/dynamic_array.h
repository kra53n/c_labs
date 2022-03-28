#ifndef DYNARRAY_H
#define DYNARRAY_H

int askUserAboutNumber(char const title[]);

float** mallocArray2D();

float** reallocArray2D(float** arr, int num);

int getArray2DSize(float** arr);

float** getArray2DWithAddedRow(float** arr, int row, int cols);

float** getArray2DWithDeletedRow(float** arr, int row);

void mallocArray2DForArray(float** arr, int row, int cols);

void freeArray(float** arr);

float** getFilledArrayManually(float** arr);

void printArray2D(float** arr);

float** getArrayFromFile(float** arr, char filename[]);

errno_t writeArrayToFile(float** arr, char filename[]);

float** getArrayFromBinFile(float** arr, char filename[]);

errno_t writeArrayToBinFile(float** arr, char filename[]);

#endif
