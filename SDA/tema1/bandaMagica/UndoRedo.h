/* POPESCU Matei 315CB*/
#include <stdio.h>
#include "Banda.h"
#ifndef TEMA1_UNDOREDO_H
#define TEMA1_UNDOREDO_H

typedef struct stack {
    char *comanda;
    struct stack *urm;
}TCelulaStiva, *TStiva;

TStiva initSivaUndoRedo();
void push(TStiva *varf, char *comanda);
char *pop(TStiva *vf, TCelula *deget, char *UNDO_REDO);
void clearStack(TStiva *undo, TStiva *redo);

#endif //TEMA1_UNDOREDO_H
