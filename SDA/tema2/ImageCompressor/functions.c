#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "tree.h"
#include "queue.h"
#include "gettingData.h"
#include "image.h"

void putInfoInNode(TArb aux, TPixel info, int tip, int nivel) {
    aux->info = info;
    aux->type = tip;
    aux->level = nivel;
}

TArb getCompressionTree(TPixel **matrix, unsigned int x, unsigned int y, unsigned int size, int factor, int nivel) {
    TArb aux = malloc(sizeof(TNod));
    if (getMean(matrix, size, x, y) <= (unsigned long long)factor) {
        putInfoInNode(aux, colorAverage(matrix, size, x, y), 1, nivel);
        return aux;
    } else {
        aux->type = 0;
        aux->n1 = getCompressionTree(matrix, x, y, size / 2, factor, nivel);
        aux->n2 = getCompressionTree(matrix, x, y + size / 2, size / 2, factor, nivel);
        aux->n3 = getCompressionTree(matrix, x + size / 2, y + size / 2, size / 2, factor, nivel);
        aux->n4 = getCompressionTree(matrix, x + size / 2, y, size / 2, factor, nivel);
    }
    return aux;
}

TLista initNode(TArb info) {
    TLista celulaNoua = (TLista)calloc(1, sizeof(TCelula));
    if(!celulaNoua) {
        return NULL;
    }
    celulaNoua->next = NULL;
    celulaNoua->info = calloc(1, sizeof(TArb));
    celulaNoua->info = info;
    return celulaNoua;
}

void addValueToQueue(TArb value, TQueue *q) {
    TLista aux = initNode(value);
    if (q->start == NULL) {
        q->start = aux;
        q->end = aux;
        return;
    }
    q->end->next = aux;
    q->end = aux;
}

TArb deleteFromQueue(TQueue *q) {
    if (q->start == NULL && q->end == NULL) {
        return NULL;
    }

    TLista aux = q->start;
    TArb a = aux->info;

    if (q->start == q->end) {
        q->start = q->end = NULL;
        return a;
    }

    q->start = aux->next;
    free(aux);
    return a;
}

void convertTreeToQueue(TArb arb, TQueue *q, FILE *output) {
    if(arb == NULL) {
        return;
    }

    addValueToQueue(arb, q);
    while (q->start != NULL) {
        TArb aux = deleteFromQueue(q);
        if (aux->n1 == NULL) {
            fwrite(&aux->type, sizeof(unsigned char), 1, output);
            fwrite(&aux->info.red, sizeof(unsigned char), 1, output);
            fwrite(&aux->info.green, sizeof(unsigned char), 1, output);
            fwrite(&aux->info.blue, sizeof(unsigned char), 1, output);

        } else {
            fwrite(&aux->type, sizeof(unsigned char), 1, output);
            addValueToQueue(aux->n1, q);
            addValueToQueue(aux->n2, q);
            addValueToQueue(aux->n3, q);
            addValueToQueue(aux->n4, q);
        }
    }
}

void getTreeFromFile(TArb root, FILE *input) {
    TQueue *q = (TQueue*) malloc(sizeof(TQueue));
    q->start = NULL;
    q->end = NULL;
    addValueToQueue(root, q);

    while(!feof(input) && q->start != NULL) { // while !end_of_file
        TArb aux = deleteFromQueue(q);
        unsigned char tip;
        fread(&tip, sizeof(unsigned char), 1, input);

        if (tip == 1) {
            aux->type = tip;
            fread(&aux->info.red, sizeof(unsigned char), 1, input);
            fread(&aux->info.green, sizeof(unsigned char), 1, input);
            fread(&aux->info.blue, sizeof(unsigned char), 1, input);
        } else {
            aux->type = 0;
            aux->n1 = malloc(sizeof(TNod));
            aux->n2 = malloc(sizeof(TNod));
            aux->n3 = malloc(sizeof(TNod));
            aux->n4 = malloc(sizeof(TNod));

            addValueToQueue(aux->n1, q);
            addValueToQueue(aux->n2, q);
            addValueToQueue(aux->n3, q);
            addValueToQueue(aux->n4, q);
        }
    }
}

void createMatrixFromTree(TArb a, TPixel **matrix, unsigned int size, unsigned int x, unsigned int y) {
    if (a->type == 1) {
        for (unsigned int  i = x; i < x + size; i++) {
            for (unsigned int j = y; j < y + size; j++) {
                matrix[i][j].red = a->info.red;
                matrix[i][j].green = a->info.green;
                matrix[i][j].blue = a->info.blue;
            }
        }
    } else {
        createMatrixFromTree(a->n1, matrix, size / 2, x, y);
        createMatrixFromTree(a->n2, matrix, size / 2, x, y + (size / 2));
        createMatrixFromTree(a->n3, matrix, size / 2, x + (size / 2), y + (size / 2));
        createMatrixFromTree(a->n4, matrix, size / 2, x + (size / 2), y);
    }
}

void createPPMFile(TPixel **matrix, FILE* output, unsigned int size) {
    unsigned char max_size = 255;
    // create header of the PPM file
    fprintf(output, "%s", "P6\n");
    fprintf(output, "%u %u\n", size, size);
    fprintf(output, "%d\n", max_size);

    // write the image below the header
    for (int i = 0; i < size; i++) {
        for (int j = 0; j< size; j++) {
            fwrite(&matrix[i][j].red, sizeof(unsigned char), 1, output);
            fwrite(&matrix[i][j].green, sizeof(unsigned char), 1, output);
            fwrite(&matrix[i][j].blue, sizeof(unsigned char), 1, output);
        }
    }
}

void printMatrix(TPatrat patrat, FILE *output) {
    for (int i = 0; i < patrat.size; i++) {
        for (int j = 0; j < patrat.size; j++) {
            fprintf(output, "{%d, %d, %d} ", patrat.pixelMatrix[i][j].red, patrat.pixelMatrix[i][j].green, patrat.pixelMatrix[i][j].blue);
        }
        fprintf(output, "\n");
    }
    fclose(output);
}