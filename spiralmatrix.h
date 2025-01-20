#ifndef SPIRALMATRIX_H
#define SPIRALMATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "conversion.h"

typedef struct _SpiralMatrix SpiralMatrix;

struct _SpiralMatrix {
    int size;
    int orientation;
    int rotation;
    int** matrix;
};

SpiralMatrix* generateMatrix(int size, int orientation, int rotation);
int fillMatrix(SpiralMatrix* spiralMatrix);
SpiralMatrix* freeMatrix(SpiralMatrix* spiralMatrix);
int printMatrix(SpiralMatrix* spiralMatrix, FILE* file);
int saveMatrix(SpiralMatrix* spiralMatrix);
SpiralMatrix* loadMatrix(char* fileName);

#endif