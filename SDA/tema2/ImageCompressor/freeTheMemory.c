#include <stdlib.h>

#include "tree.h"
#include "queue.h"
#include "freeTheMemory.h"

void freeMatrix(TPixel **matrix, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeQuadTree(QuadTree tree) {
    if (!tree) {
        return;
    }

    freeQuadTree(tree->n1);
    freeQuadTree(tree->n2);
    freeQuadTree(tree->n3);
    freeQuadTree(tree->n4);
    free(tree);
}