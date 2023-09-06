#include <stdio.h>
#include "structs.h"
#ifndef TEMA2_FUNCTII_H
#define TEMA2_FUNCTII_H

void readPictureData(TImagine *imagine);
void readImageMatrix(TImagine *imagine, TPatrat *patrat);
TPixel colorAverage(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y);
unsigned long long getMean(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y);
void printMatrix(TPatrat patrat, FILE *output);
TArb getCompressionTree(TPixel **matrix, unsigned int x, unsigned int y, unsigned int size, int factor, int nivel);
int getLeafs(TArb arb);
int getLevels(TArb arb);
int getLargestSquareSize(TArb arb, int level);
void convertTreeToQueue(TArb arb, TQueue *q, FILE *output);
void getTreeFromFile(TArb root, FILE *input);
void createMtrixFromTree(TArb a, TPixel **matrix, unsigned int size, unsigned int x, unsigned int y);
void createPPMFile(TPixel **matrix, FILE* output, unsigned int size);

#endif //TEMA2_FUNCTII_H
