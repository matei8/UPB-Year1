#include <stdio.h>
#ifndef TEMA2_STRUCTS_H
#define TEMA2_STRUCTS_H

// structura pentru stocarea informatiiloe despre intreaga imagine
typedef struct {
    FILE *input; // pointer la fisierul la de citit
    unsigned int width;
    unsigned int height;
    unsigned int max_size_color; // culoarea maxima pentru RGB
    unsigned int imgSize; // dimensiunea pozei
} TImagine;

// structura pentru informatiile unui pixel RGB
typedef struct pixel {
    unsigned char red, green, blue;
} TPixel;

// structura unui patrat cu dimensiunea size si o matrice de pixeli
typedef struct patrat {
    TPixel **pixelMatrix;
    unsigned int size;
    unsigned int x;
    unsigned int y;
} TPatrat;

/* structura unui nod cu pointeri la alte 4 noduri, fiecare reprezentand un patrat
 * pastrand si tipul nodului (0/1) si nivelul pe care se afla
 */

typedef struct nod {
    int nivel;
    TPixel info;
    unsigned char tip;
    struct nod *n1, *n2, *n3, *n4;
} TNod, *TArb;

// structurile folosite pentru coada

typedef struct celula {
    TArb info;
    struct celula *next;
} TCelula, *TLista;

typedef struct queue {
    TLista start, end;
} TQueue;

#endif //TEMA2_STRUCTS_H
