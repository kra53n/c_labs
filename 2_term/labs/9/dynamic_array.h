#ifndef DYNARRAY_H
#define DYNARRAY_H

float** mallocArray2D();

float** reallocArray2D(float** arr, int num);

void mallocArray2DForArray(float **arr, int row, int cols);

void freeArray(float** arr);

void fillArrayManually(float **arr);

void printArray2D(float **arr);

float** getArrayFromFile(float** arr, char filename[]);

errno_t writeArrayToFile(float** arr, char filename[]);

float** getArrayFromBinFile(float** arr, char filename[]);

errno_t writeArrayToBinFile(float** arr, char filename[]);

#endif
