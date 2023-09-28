#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "functions.h"
#include "gettingData.h"
#include "freeTheMemory.h"

void c1(QuadTree arb, FILE *output, TImage *image, int levelNo) {
    int levels_number, leafsNo;

    leafsNo = getLeafs(arb);
    levels_number = getLevels(arb);

    fprintf(output, "%d\n", levels_number);
    fprintf(output, "%d\n", leafsNo);
    fprintf(output, "%d\n", (int)(image->width / pow(2, levelNo)));
}

int main(__attribute__((unused)) int argc, char *argv[]) {
    // execute tasks------------------------------------------------------------------------------------------
    if (strcmp(argv[1], "-d") != 0) { // check if is task1 or task2
        int factor = atoi(argv[2]); // getting the decompression factor from string

        // get the image data---------------------------------------------------------------------------------
        TImage *image;
        image = (TImage *)malloc(sizeof(TImage));
        image->input = fopen(argv[3], "r+");

        readPictureData(image);

        FILE *output;
        output = fopen(argv[4], "w+");

        TSquare *square = malloc(sizeof(TSquare));
        square->size = image->width;
        square->x = 0;
        square->y = 0;

        // read the matrix from the file
        readImageMatrix(image, square);

        // get the compression tree---------------------------------------------------------------------------
        QuadTree quadTree = getCompressionTree(square->pixelMatrix, square->x, square->y, square->size, factor);

        // execute either task 1 or 2
        if (strcmp(argv[1], "-c1") == 0) {
            // generate the no of levels of the quadtree:
            int squareLevelsNo = getLargestSquareSize(quadTree, 0);
            // execute first task:
            c1(quadTree, output, image, squareLevelsNo);

        } else if (strcmp(argv[1], "-c2") == 0) {
            fwrite(&(image->width), sizeof(unsigned int), 1, output);
            TQueue *queue = (TQueue *) malloc(sizeof(TQueue));
            queue->start = NULL;
            queue->end = NULL;
            convertTreeToQueue(quadTree, queue, output);
        }

        fclose(image->input);
        free(image);
        freeMatrix(square->pixelMatrix, square->size);
        free(square);
        freeQuadTree(quadTree);

    } else { // execute task3 where many of the variables and data from task1/task2 are useless
        FILE *input = fopen(argv[2], "rb");
        FILE *output = fopen(argv[3], "wb");
        QuadTree decompression_tree = malloc(sizeof(TNode));

        unsigned int size;
        fread(&size, sizeof(unsigned int), 1, input);

        TPixel **matrix = malloc((size + 1) * sizeof(TPixel *));
        for(int i = 0; i < size + 1; i++) {
            matrix[i] = malloc((size + 1) * sizeof(TPixel));
        }

        getTreeFromFile(decompression_tree, input);
        createMatrixFromTree(decompression_tree, matrix, size, 0, 0);
        createPPMFile(matrix, output, size);

        fclose(input);
        fclose(output);
    }

    return 0;
}