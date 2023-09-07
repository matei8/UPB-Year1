#include <stdio.h>

#include "tree.h"
#include "queue.h"
#include "image.h"

#ifndef IMAGECOMPRESSOR_GETTINGDATA_H
#define IMAGECOMPRESSOR_GETTINGDATA_H

void readPictureData(TImagine *imagine);
void readImageMatrix(TImagine *imagine, TPatrat *patrat);

TPixel colorAverage(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y);
unsigned long long getMean(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y);
int getLeafs(TArb arb);
int getLevels(TArb arb);
int getLargestSquareSize(TArb arb, int level);

#endif //IMAGECOMPRESSOR_GETTINGDATA_H
