#include <stdio.h>

#include "image.h"

#ifndef TEMA2_STRUCTS_H
#define TEMA2_STRUCTS_H

// squared pixel grid  data
typedef struct patrat {
    TPixel **pixelMatrix; // pixel grid
    unsigned int size; // size of the grid
    // the coordinates of the beginning of the grid:
    unsigned int x;
    unsigned int y;
} TSquare;

// quadtree structure with four sons per root
typedef struct nod {
    TPixel info;
    unsigned char type;
    struct nod *n1, *n2, *n3, *n4;
} TNode, *QuadTree;

#endif //TEMA2_STRUCTS_H
