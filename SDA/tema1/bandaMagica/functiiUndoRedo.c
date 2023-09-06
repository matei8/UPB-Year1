#include <stdlib.h>
#include <string.h>
#include "UndoRedo.h"
#include "Banda.h"

TStiva initSivaUndoRedo() { // initialize the stack
    TStiva stiva = (TStiva) malloc(sizeof(TStiva));
    stiva->comanda = calloc(20, sizeof(char));
    stiva->urm = NULL;
    return stiva;
}

void push(TStiva *varf, char *comanda) { // adding a command in the stack for UNDO or REDO
    TStiva aux = (TStiva) malloc(sizeof(TCelulaStiva));
    if (aux == NULL) {
        return;
    }
    aux->comanda = comanda;
    aux->urm = NULL;
    aux->urm = (*varf);
    (*varf) = aux;
}

char *pop(TStiva *vf, TCelula *deget, char *UNOD_REDO) {
    char *com = malloc(20 * sizeof(char));
    strcpy(com, (*vf)->comanda);

    // depending on the command (UNDO\REDO) we will execute the command itself, or its opposite

    if (strcmp(UNOD_REDO, "UNDO") == 0) {
        if (strstr((*vf)->comanda, "LEFT") != NULL) {
            MOVE_RIGHT(deget);
        } else {
            MOVE_LEFT(deget);
        }
    } else {
        if (strstr((*vf)->comanda, "LEFT") != NULL) {
            MOVE_LEFT(deget);
        } else {
            MOVE_RIGHT(deget);
        }
    }

    TStiva aux;
    aux = *vf;
    *vf = aux->urm;
    free(aux);
    return com;
}

void clearStack(TStiva *undo, TStiva *redo) { // freeing the memory allocated for both of the stacks
    TStiva aux;
    while ((*undo) != NULL) {
        aux = (*undo);
        (*undo) = (*undo)->urm;
        free(aux->comanda);
        free(aux);
    }

    while ((*redo) != NULL) {
        aux = (*redo);
        (*redo) = (*redo)->urm;
        free(aux->comanda);
        free(aux);
    }
}