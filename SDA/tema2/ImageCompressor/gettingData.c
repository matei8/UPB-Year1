#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "image.h"
#include "functions.h"
#include "tree.h"
#include "queue.h"
#include "gettingData.h"

void readPictureData(TImagine *imagine) {
    unsigned char *image_type_buffer = malloc(3 * sizeof(char));
    fscanf(imagine->input, "%s", image_type_buffer);

    fscanf(imagine->input, "%d", &(imagine->width));
    fscanf(imagine->input, "%d", &(imagine->height));
    fscanf(imagine->input, "%d", &(imagine->max_size_color));

    imagine->imgSize = imagine->height * imagine->width;

    unsigned char new_line_buffer;
    fscanf(imagine->input, "%c", &new_line_buffer);

    free(image_type_buffer);
}

void readImageMatrix(TImagine *imagine, TPatrat *patrat) {
    unsigned int size = patrat->size;

    patrat->pixelMatrix = malloc(size * sizeof(TPixel *));
    for (int i = 0; i < size + 1; i++) {
        patrat->pixelMatrix[i] = malloc(size * sizeof(TPixel));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fread(&(patrat->pixelMatrix[i][j]).red, sizeof(unsigned char), 1, imagine->input);
            fread(&(patrat->pixelMatrix[i][j]).green, sizeof(unsigned char), 1, imagine->input);
            fread(&(patrat->pixelMatrix[i][j]).blue, sizeof(unsigned char), 1, imagine->input);
        }
    }
}

TPixel colorAverage(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y) {
    TPixel average;
    unsigned long averageRed = 0, averageGreen = 0, averageBlue = 0, i, j;

    for (i = x; i < (x + size); i++) {
        for (j = y; j < (y + size); j++) {
            averageRed += (unsigned long)pixelMatrix[i][j].red;
            averageGreen += (unsigned long)pixelMatrix[i][j].green;
            averageBlue += (unsigned long)pixelMatrix[i][j].blue;
        }
    }

    averageRed /= (size * size);
    averageGreen /= (size * size);
    averageBlue /= (size * size);

    average.red = (unsigned char)averageRed;
    average.green = (unsigned char)averageGreen;
    average.blue = (unsigned char)averageBlue;

    return average;
}

unsigned long long getMean(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y) {
    unsigned long long mean = 0, i, j;
    TPixel average = colorAverage(pixelMatrix, size, x, y);

    for (i = x; i < size + x; i++) {
        for (j = y; j < size + y; j++) {

            int redFactor = (average.red - pixelMatrix[i][j].red);
            int greenFactor = (average.green - pixelMatrix[i][j].green);
            int blueFactor = (average.blue - pixelMatrix[i][j].blue);

            mean += (unsigned long long)(pow(redFactor, 2) + pow(greenFactor, 2) + pow(blueFactor, 2));
        }
    }

    mean /= (3 * size * size);
    return mean;
}

int getLeafs(TArb arb) {
    int nrFrunze;
    if (arb == NULL) {
        return 0;
    }

    nrFrunze = getLeafs(arb->n1);
    nrFrunze += getLeafs(arb->n2);
    nrFrunze += getLeafs(arb->n3);
    nrFrunze += getLeafs(arb->n4);
    if (arb->type == 1) {
        nrFrunze++;
    }

    return nrFrunze;
}

int min(int a, int b) {
    if(a > b) {
        return b;
    } else {
        return a;
    }
}

int max(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

int getLevels(TArb arb) {
    if(arb == NULL) {
        return 0;
    }

    int n1Level = getLevels(arb->n1);
    int n2Level = getLevels(arb->n2);
    int n3Level = getLevels(arb->n3);
    int n4Level = getLevels(arb->n4);

    int current = max(max(n1Level, n2Level), max(n3Level, n4Level));
    arb->level = current + 1;
    int nrLevel = current + 1;

    return nrLevel;
}

int getLargestSquareSize(TArb arb, int level) {
    if (arb == NULL) {
        return 0;
    }

    if (arb->type == 1) {
        return level;
    }

    int minN1 = getLargestSquareSize(arb->n1, level + 1);
    int minN2 = getLargestSquareSize(arb->n2, level + 1);
    int minN3 = getLargestSquareSize(arb->n3, level + 1);
    int minN4 = getLargestSquareSize(arb->n4, level + 1);

    int min12 = min(minN1, minN2);
    int min34 = min(minN3, minN4);
    int min_check = min(min12, min34);

    return min_check;
}