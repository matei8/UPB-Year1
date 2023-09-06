#include <stdio.h>
#include "Banda.h"
#include "UndoRedo.h"

#ifndef TEMA1_COMENZI_H
#define TEMA1_COMENZI_H

typedef struct celula2 {
    char *info;
    struct celula2 *next;
} TComanda, *TListaCom;

typedef struct coada {
    TListaCom inceput, sfarsit;
} TComenzi;

TComenzi *initCoadaComenzi();
void adaugaComanda(TComenzi *coada, char *com);
void afisareComenzi(TComenzi *c); // for debugging purposes only!!!
void *citesteComenzi(TComenzi *coadaComenzi, TCelula *deget, TBanda banda, TStiva *undo, TStiva *redo);
void elibereazaCoada(TComenzi *c);
void EXECUTE(TComenzi *coadaComenzi, TCelula *deget, FILE *output, TStiva *undo, TStiva *redo);

#endif
