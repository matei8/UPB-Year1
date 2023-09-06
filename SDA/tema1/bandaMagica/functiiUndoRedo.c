/* POPESCU Matei 315CB*/
#include <stdlib.h>
#include <string.h>
#include "UndoRedo.h"
#include "Banda.h"

TStiva initSivaUndoRedo() { //imitializarea stivei
    TStiva stiva = (TStiva) malloc(sizeof(TStiva));
    stiva->comanda = calloc(20, sizeof(char));
    stiva->urm = NULL;
    return stiva;
}

void push(TStiva *varf, char *comanda) { //adaugarea unei comenzi noi fie in UNDO, fie in REDO
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

    //in functie de comanda (UNDO\REDO) vom execute comanda, sau inversul comenzii

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

void clearStack(TStiva *undo, TStiva *redo) { //eliberarea celor doua stive
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