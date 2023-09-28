#include <stdio.h>

#include "tree.h"
#include "queue.h"
#include "image.h"

#ifndef TEMA2_FUNCTII_H
#define TEMA2_FUNCTII_H

void printMatrix(TSquare square, FILE *output); // for debugging purposes only
QuadTree getCompressionTree(TPixel **matrix, unsigned int x, unsigned int y, unsigned int size, int factor);
void convertTreeToQueue(QuadTree arb, TQueue *q, FILE *output);
void getTreeFromFile(QuadTree root, FILE *input);
void createMatrixFromTree(QuadTree a, TPixel **matrix, unsigned int size, unsigned int x, unsigned int y);
void createPPMFile(TPixel **matrix, FILE* output, unsigned int size);

#endif //TEMA2_FUNCTII_H
