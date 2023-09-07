#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "tree.h"
#include "functions.h"
#include "queue.h"
#include "gettingData.h"
#include "image.h"

void c1(TArb arb, FILE *output, TImagine *imagine, int nrLevel) {
    int nrNiveluri, nrFrunze;

    nrFrunze = getLeafs(arb);
    nrNiveluri = getLevels(arb);

    fprintf(output, "%d\n", nrNiveluri);
    fprintf(output, "%d\n", nrFrunze);
    fprintf(output, "%d\n", (int)(imagine->width / pow(2, nrLevel)));
}

int main(int argc, char *argv[]) {
    // execute tasks------------------------------------------------------------------------------------------
    if (strcmp(argv[1], "-d") != 0) { // check if is task1 or task2
        int factor = atoi(argv[2]); // getting the decompression factor from string

        // get the image data---------------------------------------------------------------------------------
        TImagine *imagine;
        imagine = (TImagine *)malloc(sizeof(TImagine));
        imagine->input = fopen(argv[3], "r+");

        readPictureData(imagine);

        FILE *output;
        output = fopen(argv[4], "w+");

        TPatrat *patrat = malloc(sizeof(TPatrat));
        patrat->size = imagine->width;
        patrat->x = 0;
        patrat->y = 0;

        // read the matrix from the file
        readImageMatrix(imagine, patrat);

        // get the compression tree---------------------------------------------------------------------------
        TArb arb = getCompressionTree(patrat->pixelMatrix, patrat->x, patrat->y, patrat->size, factor, 0);

        // execute either task 1 or 2
        if (strcmp(argv[1], "-c1") == 0) {
            int nrLevel = getLargestSquareSize(arb, 0);
            c1(arb, output, imagine, nrLevel);

        } else if (strcmp(argv[1], "-c2") == 0) {
            fwrite(&(imagine->width), sizeof(unsigned int), 1, output);
            TQueue *queue = (TQueue *) malloc(sizeof(TQueue));
            queue->start = NULL;
            queue->end = NULL;
            convertTreeToQueue(arb, queue, output);
        }

        fclose(imagine->input);
        free(imagine);
        freeMatrix(patrat);
    } else {
        FILE *input = fopen(argv[2], "rb");
        FILE *output = fopen(argv[3], "wb");
        TArb decomp = malloc(sizeof(TNod));
        unsigned int size;
        fread(&size, sizeof(unsigned int), 1, input);

        TPixel **matrix = malloc((size + 1) * sizeof(TPixel *));
        for(int i = 0; i < size + 1; i++) {
            matrix[i] = malloc((size + 1) * sizeof(TPixel));
        }

        getTreeFromFile(decomp, input);
        createMatrixFromTree(decomp, matrix, size, 0, 0);
        createPPMFile(matrix, output, size);

        fclose(input);
        fclose(output);
    }

    return 0;
}