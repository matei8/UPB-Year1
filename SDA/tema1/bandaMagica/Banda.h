/* POPESCU Matei 315CB*/
#include <stdio.h>

#ifndef TEMA1_BANDA_H
#define TEMA1_BANDA_H

typedef struct celula {
    char info;
    struct celula *urm, *prev;
} *TCelula;

typedef struct banda {
   TCelula santinela;
   TCelula deget;
} *TBanda;

TCelula alocCelula(char valoare);
TBanda initBanda();
void elibereazaBanda(TBanda banda);

void WRITE(TCelula *deget, char val);
void MOVE_LEFT(TCelula *deget);
void MOVE_RIGHT(TCelula *deget);
void INSERT_LEFT(TCelula *deget, char val, FILE *output);
void INSERT_RIGHT(TCelula *deget, char val);
void MOVE_RIGHT_CHAR(TCelula *deget, char val);
void MOVE_LEFT_CHAR(TCelula *deget, char val, FILE *output);

void SHOW(TBanda banda, TCelula *deget, FILE *output);
void SHOW_CURRENT(TCelula *deget, FILE *output);

#endif
