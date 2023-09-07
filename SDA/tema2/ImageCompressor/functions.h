#include <stdio.h>

#include "tree.h"
#include "queue.h"
#include "image.h"

#ifndef TEMA2_FUNCTII_H
#define TEMA2_FUNCTII_H

void printMatrix(TPatrat patrat, FILE *output); // for debugging purposes only
TArb getCompressionTree(TPixel **matrix, unsigned int x, unsigned int y, unsigned int size, int factor, int nivel);
void convertTreeToQueue(TArb arb, TQueue *q, FILE *output);
void getTreeFromFile(TArb root, FILE *input);
void createMatrixFromTree(TArb a, TPixel **matrix, unsigned int size, unsigned int x, unsigned int y);
void createPPMFile(TPixel **matrix, FILE* output, unsigned int size);

#endif //TEMA2_FUNCTII_H
