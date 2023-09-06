#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structs.h"
#include "functii.h"

void c1(TArb arb, FILE *output, TImagine *imagine, int nrLevel) {
    int nrNiveluri = 0, nrFrunze;

    nrFrunze = getLeafs(arb);
    nrNiveluri = getLevels(arb);

    fprintf(output, "%d\n", nrNiveluri);
    fprintf(output, "%d\n", nrFrunze);
    fprintf(output, "%d\n", (int)(imagine->width / pow(2, nrLevel)));
}

int main(int argc, char *argv[]) {
    // get task and factor from CLI---------------------------------------------------------------------------
    char *cerinta = malloc(3 * sizeof(char));
    strcpy(cerinta, argv[1]);

    // execute task--------------------------------------------------------------------------------------------
    if (strcmp(cerinta, "-d") != 0) {
        int factor = atoi(argv[2]);

        // get the image data-------------------------------------------------------------------------------------
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

        readImageMatrix(imagine, patrat);

        // get compression tree------------------------------------------------------------------------------------
        unsigned long long mean = getMean(patrat->pixelMatrix, patrat->size, patrat->x, patrat->y);

        TArb arb = getCompressionTree(patrat->pixelMatrix, patrat->x, patrat->y, patrat->size, factor, 0);

        if (strcmp(cerinta, "-c1") == 0) {
            int nrLevel = getLargestSquareSize(arb, 0);
            c1(arb, output, imagine, nrLevel);
        } else if (strcmp(cerinta, "-c2") == 0) {
            fwrite(&(imagine->width), sizeof(unsigned int), 1, output);
            TQueue *queue = (TQueue *) malloc(sizeof(TQueue));
            queue->start = NULL;
            queue->end = NULL;
            convertTreeToQueue(arb, queue, output);
        }

        fclose(imagine->input);
        free(imagine);
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
        createMtrixFromTree(decomp, matrix, size, 0, 0);
        createPPMFile(matrix, output, size);
        fclose(input);
        fclose(output);
    }
    return 0;
}