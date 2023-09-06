#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "functii.h"
#include "structs.h"

void readPictureData(TImagine *imagine) {
    unsigned char *image_type_buffer = malloc(3 * sizeof(char));
    fscanf(imagine->input, "%s", image_type_buffer);

    fscanf(imagine->input, "%d", &(imagine->width));
    fscanf(imagine->input, "%d", &(imagine->height));
    fscanf(imagine->input, "%d", &(imagine->max_size_color));

    imagine->imgSize = imagine->height * imagine->width;

    unsigned char new_line_buffer;
    fscanf(imagine->input, "%c", &new_line_buffer);

    free(image_type_buffer);
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

void readImageMatrix(TImagine *imagine, TPatrat *patrat) {
    unsigned int size = patrat->size;

    patrat->pixelMatrix = malloc(size * sizeof(TPixel *));
    for (int i = 0; i < size + 1; i++) {
        patrat->pixelMatrix[i] = malloc(size * sizeof(TPixel));
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fread(&(patrat->pixelMatrix[i][j]).red, sizeof(unsigned char), 1, imagine->input);
            fread(&(patrat->pixelMatrix[i][j]).green, sizeof(unsigned char), 1, imagine->input);
            fread(&(patrat->pixelMatrix[i][j]).blue, sizeof(unsigned char), 1, imagine->input);
        }
    }
}

TPixel colorAverage(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y) {
    TPixel average;
    unsigned long averageRed = 0, averageGreen = 0, averageBlue = 0, i, j;

    for (i = x; i < (x + size); i++) {
        for (j = y; j < (y + size); j++) {
            averageRed += (unsigned long)pixelMatrix[i][j].red;
            averageGreen += (unsigned long)pixelMatrix[i][j].green;
            averageBlue += (unsigned long)pixelMatrix[i][j].blue;
        }
    }

    averageRed /= (size * size);
    averageGreen /= (size * size);
    averageBlue /= (size * size);

    average.red = (unsigned char)averageRed;
    average.green = (unsigned char)averageGreen;
    average.blue = (unsigned char)averageBlue;

    return average;
}

unsigned long long getMean(TPixel **pixelMatrix, unsigned int size, unsigned int x, unsigned int y) {
    unsigned long long mean = 0, i, j;
    TPixel average = colorAverage(pixelMatrix, size, x, y);

    for (i = x; i < size + x; i++) {
        for (j = y; j < size + y; j++) {

            int redFactor = (average.red - pixelMatrix[i][j].red);
            int greenFactor = (average.green - pixelMatrix[i][j].green);
            int blueFactor = (average.blue - pixelMatrix[i][j].blue);

            mean += (unsigned long long)(pow(redFactor, 2) + pow(greenFactor, 2) + pow(blueFactor, 2));
        }
    }

    mean /= (3 * size * size);
    return mean;
}

void freePixMatrix(TPatrat *patrat) {
    for (unsigned int i = patrat->x; i < patrat->size + patrat->x; i++) {
        free(patrat->pixelMatrix[i]);
    }
}

void putInfoInNode(TArb aux, TPixel info, int tip, int nivel) {
    aux->info = info;
    aux->tip = tip;
    aux->nivel = nivel;
}

TArb getCompressionTree(TPixel **matrix, unsigned int x, unsigned int y, unsigned int size, int factor, int nivel) {
    TArb aux = malloc(sizeof(TNod));
    if (getMean(matrix, size, x, y) <= (unsigned long long)factor) {
        putInfoInNode(aux, colorAverage(matrix, size, x, y), 1, nivel);
        return aux;
    } else {
        aux->tip = 0;
        aux->n1 = getCompressionTree(matrix, x, y, size / 2, factor, nivel);
        aux->n2 = getCompressionTree(matrix, x, y + size / 2, size / 2, factor, nivel);
        aux->n3 = getCompressionTree(matrix, x + size / 2, y + size / 2, size / 2, factor, nivel);
        aux->n4 = getCompressionTree(matrix, x + size / 2, y, size / 2, factor, nivel);
    }
    return aux;
}

int getLeafs(TArb arb) {
    int nrFrunze;
    if (arb == NULL) {
        return 0;
    }

    nrFrunze = getLeafs(arb->n1);
    nrFrunze += getLeafs(arb->n2);
    nrFrunze += getLeafs(arb->n3);
    nrFrunze += getLeafs(arb->n4);
    if (arb->tip == 1) {
        nrFrunze++;
    }

    return nrFrunze;
}

int min(int a, int b) {
    if(a > b) {
        return b;
    } else {
        return a;
    }
}

int max(int a, int b) {
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

int getLevels(TArb arb) {
    if(arb == NULL) {
        return 0;
    }

    int n1Level = getLevels(arb->n1);
    int n2Level = getLevels(arb->n2);
    int n3Level = getLevels(arb->n3);
    int n4Level = getLevels(arb->n4);

    int curent = max(max(n1Level, n2Level), max(n3Level, n4Level));
    arb->nivel = curent + 1;
    int nrLevel = curent + 1;

    return nrLevel;
}

int getLargestSquareSize(TArb arb, int level) {
    if (arb == NULL) {
        return 0;
    }

    if (arb->tip == 1) {
        return level;
    }

    int minN1 = getLargestSquareSize(arb->n1, level + 1);
    int minN2 = getLargestSquareSize(arb->n2, level + 1);
    int minN3 = getLargestSquareSize(arb->n3, level + 1);
    int minN4 = getLargestSquareSize(arb->n4, level + 1);

    int min12 = min(minN1, minN2);
    int min34 = min(minN3, minN4);
    int min_check = min(min12, min34);

    return min_check;
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
            fwrite(&aux->tip, sizeof(unsigned char), 1, output);
            fwrite(&aux->info.red, sizeof(unsigned char), 1, output);
            fwrite(&aux->info.green, sizeof(unsigned char), 1, output);
            fwrite(&aux->info.blue, sizeof(unsigned char), 1, output);

        } else {
            fwrite(&aux->tip, sizeof(unsigned char), 1, output);
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

    while(!feof(input) && q->start != NULL) {
        TArb aux = deleteFromQueue(q);
        unsigned char tip;
        fread(&tip, sizeof(unsigned char), 1, input);

        if (tip == 1) {
            aux->tip = tip;
            fread(&aux->info.red, sizeof(unsigned char), 1, input);
            fread(&aux->info.green, sizeof(unsigned char), 1, input);
            fread(&aux->info.blue, sizeof(unsigned char), 1, input);
        } else {
            aux->tip = 0;
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

void createMtrixFromTree(TArb a, TPixel **matrix, unsigned int size, unsigned int x, unsigned int y) {
    if (a->tip == 1) {
        for (int  i = x; i < x + size; i++) {
            for (int j = y; j < y + size; j++) {
                matrix[i][j].red = a->info.red;
                matrix[i][j].green = a->info.green;
                matrix[i][j].blue = a->info.blue;
            }
        }
    } else {
        createMtrixFromTree(a->n1, matrix, size / 2, x, y);
        createMtrixFromTree(a->n2, matrix, size / 2, x, y + (size / 2));
        createMtrixFromTree(a->n3, matrix, size / 2, x + (size / 2), y + (size / 2));
        createMtrixFromTree(a->n4, matrix, size / 2, x + (size / 2), y);
    }
}

void createPPMFile(TPixel **matrix, FILE* output, unsigned int size) {
    unsigned char max_size = 255;
    fprintf(output, "%s", "P6\n");
    fprintf(output, "%u %u\n", size, size);
    fprintf(output, "%d\n", max_size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j< size; j++) {
            fwrite(&matrix[i][j].red, sizeof(unsigned char), 1, output);
            fwrite(&matrix[i][j].green, sizeof(unsigned char), 1, output);
            fwrite(&matrix[i][j].blue, sizeof(unsigned char), 1, output);
        }
    }
}