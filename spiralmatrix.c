#include "spiralmatrix.h"

SpiralMatrix* generateMatrix(int size, int orientation, int rotation) {
    SpiralMatrix* spiralMatrix = (SpiralMatrix*)malloc(sizeof(SpiralMatrix));
    if (spiralMatrix == NULL) {
        return NULL;
    }
    spiralMatrix -> matrix = (int**)malloc(sizeof(int*) * size);
    spiralMatrix -> size = size;
    spiralMatrix -> orientation = orientation;
    spiralMatrix -> rotation = rotation;
    for (int i = 0; i < size; i++) {
        spiralMatrix -> matrix[i] = (int*)malloc(sizeof(int) * size);
    }
    return spiralMatrix;
}

int fillMatrix(SpiralMatrix* spiralMatrix) {
    if (spiralMatrix == NULL) {
        return 0;
    }
    // könnyített verzió
    /* int cnt = 0;
    for (int i = 0; i < spiralMatrix -> size; i++) {
        for (int j = 0; j < spiralMatrix -> size; j++) {
            spiralMatrix -> matrix[i][j] = ++cnt;
        }
    } */
    // végleges verzió
    int x, y, offset;
    int directions[] = {0,1,2,3};
    if (spiralMatrix -> size % 2 == 1) {
        x = spiralMatrix -> size / 2;
        y = spiralMatrix -> size / 2;
    }
    else {
        if ((spiralMatrix -> orientation == 2 && spiralMatrix -> rotation == 1) || (spiralMatrix -> orientation == 1 && spiralMatrix -> rotation == 0)) {
            x = (spiralMatrix -> size / 2) - 1;
            y = (spiralMatrix -> size / 2) - 1;
        }
        else if ((spiralMatrix -> orientation == 3 && spiralMatrix -> rotation == 1) || (spiralMatrix -> orientation == 2 && spiralMatrix -> rotation == 0)) {
            x = (spiralMatrix -> size / 2) - 1;
            y = spiralMatrix -> size / 2;
        }
        else if ((spiralMatrix -> orientation == 1 && spiralMatrix -> rotation == 1) || (spiralMatrix -> orientation == 0 && spiralMatrix -> rotation == 0)) {
            x = spiralMatrix -> size / 2;
            y = (spiralMatrix -> size / 2) - 1;
        }
        else {
            x = spiralMatrix -> size / 2;
            y = spiralMatrix -> size / 2;
        }
    }
    spiralMatrix -> matrix[x][y] = 1;
    if (spiralMatrix -> rotation == 0) {
        offset = spiralMatrix -> orientation;
    }
    else {
        directions[1] = 3;
        directions[3] = 1;
        if (spiralMatrix -> orientation == 1) {
            offset = 3;
        }
        else if (spiralMatrix -> orientation == 3) {
            offset = 1;
        }
        else {
            offset = spiralMatrix -> orientation;
        }
    }
    int val = 2;
    int prevStepCount = 0;
    int curStepCount = 1;
    int stepDirection = offset;
    int i = 1;
    while (val <= spiralMatrix -> size * spiralMatrix -> size) {
        if (directions[stepDirection] == 0) {
            x--;
        }
        else if (directions[stepDirection] == 1) {
            y++;
        }
        else if (directions[stepDirection] == 2) {
            x++;
        }
        else {
            y--;
        }
        spiralMatrix -> matrix[x][y] = val;
        if (i == curStepCount) {
            if (prevStepCount == curStepCount) {
                curStepCount++;
            }
            else {
                prevStepCount = curStepCount;
            }
            stepDirection = (stepDirection + 1) % 4;
            i = 1;
        }
        else {
            i++;
        }
        val++;
    }
    
    return 1;
}

SpiralMatrix* freeMatrix(SpiralMatrix* spiralMatrix) {
    if (spiralMatrix == NULL) {
        return NULL;
    }
    for (int i = 0; i < spiralMatrix -> size; i++) {
        free(spiralMatrix -> matrix[i]);
    }
    free(spiralMatrix -> matrix);
    free(spiralMatrix);
    return NULL;
}

int printMatrix(SpiralMatrix* spiralMatrix, FILE* file) {
    if (spiralMatrix == NULL) {
        return 0;
    }
    int maxNumInMatrix = spiralMatrix -> size * spiralMatrix -> size;
    int maxPadding = floor(log10((double)maxNumInMatrix));
    for (int i = 0; i < spiralMatrix -> size; i++) {
        for (int j = 0; j < spiralMatrix -> size; j++) {
            for (int k = 0; k < (maxPadding - floor(log10((double)(spiralMatrix -> matrix[i][j])))); k++) {
                fprintf(file, " ");
            }
            fprintf(file, "%d ", spiralMatrix -> matrix[i][j]);
        }
        fprintf(file, "\n");
    }
    return 1;
}

int saveMatrix(SpiralMatrix* spiralMatrix) {
    if (spiralMatrix == NULL) {
        return 0;
    }
    // fileName = spiral_{size}_{orientation}_{rotation}.txt
    // spiral - 6 | size - 2 | orientation - 1 | rotation - 1 | _ - 3 | .txt - 4
    int fileNameLength = 18;
    char* fileName = malloc(sizeof(char) * fileNameLength);
    if (spiralMatrix -> size > 9) {
        sprintf(fileName, "spiral_%d_%c_%c.txt", spiralMatrix -> size, orientationIntToChar(spiralMatrix -> orientation), rotationIntToChar(spiralMatrix -> rotation));
    }
    else {
        sprintf(fileName, "spiral_0%d_%c_%c.txt", spiralMatrix -> size, orientationIntToChar(spiralMatrix -> orientation), rotationIntToChar(spiralMatrix -> rotation));
    }
    FILE* file = fopen(fileName, "w");
    printMatrix(spiralMatrix, file);
    fclose(file);
    free(fileName);
    return 1;
}

SpiralMatrix* loadMatrix(char* fileName) {
    char sizeString[3];
    sizeString[0] = fileName[7];
    sizeString[1] = fileName[8];
    sizeString[2] = '\0';
    int size = atoi(sizeString);
    int orientation = orientationCharToInt(fileName[10]);
    int rotation = rotationCharToInt(fileName[12]);
    SpiralMatrix* spiralMatrix = generateMatrix(size, orientation, rotation);
    fillMatrix(spiralMatrix);
    return spiralMatrix;
}