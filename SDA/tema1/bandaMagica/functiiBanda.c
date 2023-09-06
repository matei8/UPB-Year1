#include <stdio.h>
#include <stdlib.h>
#include "Banda.h"

TCelula alocCelula(char valoare) { // initialize cell from the tape
    TCelula celula = (TCelula)malloc(sizeof(TCelula));
    if (celula == NULL) {
        return NULL;
    }
    celula->info = valoare;
    celula->urm = NULL;
    celula->prev = NULL;
    return celula;
}

TBanda initBanda() { // initialize tape
    TBanda banda = (TBanda)malloc(sizeof(TCelula));
    if (banda == NULL) {
        return NULL;
    }
    banda->santinela = alocCelula(0);
    banda->deget = banda->santinela;
    return banda;
}

/* Below are defined all the  update si query functions */

void WRITE(TCelula *deget, char val) {
    (*deget)->info = val;
}

void MOVE_LEFT_CHAR(TCelula *deget, char val, FILE *output) {
    TCelula aux = (*deget);
    while (aux->info != val) { // iterate through the tape until you find the desired element
        if (aux->prev == NULL) { // if the element was not found and NULL was found, an error is displayed and the loop is exited
            fprintf(output, "%s\n", "ERROR");
            return;
        }
        aux = aux->prev;
    }
    (*deget) = aux; // the current index moves to the new position (on the element found if it exists)
}

void MOVE_RIGHT_CHAR(TCelula *deget, char val) {
    TCelula aux = (*deget);
    while (aux->info != val) {
        if (aux->urm == NULL) {
            TCelula *aux2;
            (*aux2) = alocCelula('#'); // if the desired element is not found, a new cell is inserted when NULL is encountered

            (*aux2)->prev = aux;
            (*aux2)->urm = NULL;
            aux->urm = (*aux2);
            aux = (*aux2);
            break;
        }
        aux = aux->urm;
    }
    (*deget) = aux; // the current index moves to the new position (on the element found if it exists or on the new cell)
}

void MOVE_LEFT(TCelula *deget) {
    if ((*deget)->prev == NULL || (*deget) == NULL) {
        return;
    }
    (*deget) = (*deget)->prev;
}

void MOVE_RIGHT(TCelula *deget) {
    if ((*deget)->urm == NULL) {
        TCelula aux = (TCelula) malloc(sizeof(TCelula)); // if the right cell is NULL a new cell is created
        aux->info = '#';
        aux->prev = (*deget);
        aux->urm = NULL;
        (*deget)->urm = NULL;
        (*deget)->urm = aux;
        (*deget) = aux;
    } else {
        (*deget) = (*deget)->urm;
    }
}

void INSERT_LEFT(TCelula *deget, char val, FILE *output) {
    TCelula *aux;
    (*aux) = alocCelula(val);
    if ((*deget)->prev == NULL) {
        fprintf(output, "%s\n", "ERROR");
        return;
    }

    (*aux)->urm = (*deget);
    (*aux)->prev = (*deget)->prev;
    (*deget)->prev->urm = (*aux);
    (*deget)->prev = (*aux);
    (*deget) = (*aux);
}

void INSERT_RIGHT(TCelula *deget, char val) {
    TCelula *aux;
    (*aux) = alocCelula(val);

    (*aux)->prev = (*deget);
    (*aux)->urm = (*deget)->urm;
    if ((*deget)->urm != NULL) {
        (*deget)->urm->prev = (*aux);
    }
    (*deget)->urm = NULL;
    (*deget)->urm = (*aux);
    (*deget) = (*aux);
}

void SHOW(TBanda banda, TCelula *deget, FILE *output) {
    TCelula aux = banda->santinela->urm;
    while (aux != NULL) {
        if ((*deget) == aux) {
            fprintf(output,"|%c|", aux->info); // printing the current index between bars
        } else {
            fprintf(output, "%c", aux->info);
        }
        aux = aux->urm;
    }
    fprintf(output, "%s", "\n");
}

void SHOW_CURRENT(TCelula *deget, FILE *output) {
    if ((*deget) == NULL) {
        fprintf(output, "%s","ERROR");
        return;
    }
    fprintf(output,"%c\n", (*deget)->info);
}

void elibereazaBanda(TBanda banda) { // free the memory used by the tape
    TCelula temp;
    for (temp = banda->santinela; temp != NULL;) {
        TCelula aux = temp;
        temp = temp->urm;
        free(aux);
    }
    banda->santinela = NULL;
    banda->deget = NULL;
    banda = NULL;
    free(banda);
}