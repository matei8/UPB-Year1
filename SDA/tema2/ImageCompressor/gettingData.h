#include <stdio.h>

#include "tree.h"
#include "queue.h"
#include "image.h"

#ifndef IMAGECOMPRESSOR_GETTINGDATA_H
#define IMAGECOMPRESSOR_GETTINGDATA_H

void readPictureData(TImage *imagine);
void readImageMatrix(TImage *imagine, TSquare *square);

TPixel colorAverage(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y);
unsigned long long getMean(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y);
int getLeafs(QuadTree tree);
int getLevels(QuadTree arb);
int getLargestSquareSize(QuadTree arb, int level);

#endif //IMAGECOMPRESSOR_GETTINGDATA_H
