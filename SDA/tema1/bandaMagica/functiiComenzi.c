#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comenzi.h"
#include "Banda.h"

// MACROS for the length off commands as strings

#define SIZE_W 6     // WRITE
#define SIZE_IR 13   // INSERT RIGHT
#define SIZE_IL 12   // INSERT LEFT
#define SIZE_MLC 15  // MOVE_LEFT_CHAR
#define SIZE_MRC 16  // MOVE_RIGHT_CHAR

TComenzi *initCoadaComenzi() {
    TComenzi *coadaTemp = (TComenzi *)malloc(sizeof(TComenzi));
    if(coadaTemp == NULL) {
        return NULL;
    }
    coadaTemp->inceput = coadaTemp->sfarsit = NULL;
    return coadaTemp;
}

void adaugaComanda(TComenzi *coada, char *com) {
    TListaCom comanda = (TListaCom) malloc(sizeof(TListaCom));
    comanda->info = com;
    comanda->next = NULL;

    if (coada->sfarsit != NULL) {
        coada->sfarsit->next = comanda;
    } else {
        coada->inceput = comanda;
    }

    coada->sfarsit = comanda;
}

void afisareComenzi(TComenzi *c) { // function for debugging purposes only!!!
    TListaCom aux = c->inceput;
    while (aux != NULL) {
        printf("%s\n", aux->info);
        aux = aux->next;
    }
}

void eliminaComanda(TComenzi *coadaComenzi) {
    TListaCom aux = coadaComenzi->inceput;
    if (coadaComenzi->inceput == coadaComenzi->sfarsit) {
        coadaComenzi->inceput = coadaComenzi->sfarsit = NULL;
        return;
    }
    coadaComenzi->inceput = coadaComenzi->inceput->next;
    aux->next = NULL;
    free(aux);
}

/* the function below encodes the commands received as a parameter
  * depending on the functionality of each one, classifying them as well,
  * being easier to read the code
*/

int verificaComanda(char *comanda) {
    if (strstr(comanda, "WRITE") != NULL || strstr(comanda, "INSERT") != NULL || strstr(comanda, "CHAR") != NULL) {
        return 0;
    } else if (strstr(comanda, "EXECUTE") != NULL) {
        return 1;
    } else if (strstr(comanda, "UNDO") != NULL || strstr(comanda, "REDO") != 0){
       return -1;
    } else if (strstr(comanda, "SHOW") != NULL) {
        return 2;
    }
    return 3;
}

void *citesteComenzi(TComenzi *coadaComenzi, TCelula *deget, TBanda banda, TStiva *undo, TStiva *redo) {
    FILE *input;
    FILE *output;
    input = fopen("tema1.in", "r");
    output = fopen("tema1.out", "w");

    int nrComenzi = 0;
    fscanf(input, "%d", &nrComenzi);
    char *bufferNewline = calloc(20, sizeof(char));
    fgets(bufferNewline, 20, input);

    int i;
    for (i = 0; i < nrComenzi; i++) {
        char *comanda = calloc(20, sizeof(char));
        fgets(comanda, 20, input);
        strcpy(comanda + (strlen(comanda) - 1), comanda + strlen(comanda));

        /* We use the command value (-1/0/1/2/3) to make the code easier to read and implement
         * also the check function (verificaComanda) must be executed only once for each iteration
         */
        int codComanda = verificaComanda(comanda);

        /* We check each command to see if it asks us to write
          * new values in the list (codComanda = 0) or ONLY move (codComanda = 3)
          * or must be executed (codComanda = 1), otherwise
          * means that I read an UNDO/REDO command (codComanda = -1).
          * There is also the case to display (codComanda = 2)
          * in which we have SHOW/SHOW_CURRENT
         */

        if (codComanda == 0 || codComanda == 3) {
            adaugaComanda(coadaComenzi, comanda);
        } else if (codComanda == 1) {
            EXECUTE(coadaComenzi, deget, output, undo, redo);
            continue;
        } else if (codComanda == 2) {
            if (strstr(comanda, "CURRENT") != NULL) {
                SHOW_CURRENT(deget, output);
            } else {
                SHOW(banda, deget, output);
            }
        } else {
            if (strstr(comanda, "UNDO") != NULL) {
                char *comandaRedo = pop(undo, deget, comanda);
                push(redo, comandaRedo);
            } else {
                char *comandaUndo = pop(redo, deget, comanda);
                push(undo, comandaUndo);
            }
        }
    }
    free(bufferNewline);
    fclose(output); // close INPUT/OUTPUT files
    fclose(input);
    return NULL;
}

void EXECUTE(TComenzi *coadaComenzi, TCelula *deget, FILE *output, TStiva *undo, TStiva *redo) {
    char *comanda = coadaComenzi->inceput->info;
    int codComanda = verificaComanda(comanda);

    // command + SIZE -> this is how we take from the tail of the string the value that must be found/written/inserted
    // into the tape

    if (codComanda == 0) { // search in the string for the command to be executed
        if (strstr(comanda, "WRITE") != NULL) {
            WRITE(deget, *(comanda + SIZE_W));
            clearStack(undo, redo); // if we encounter the WRITE command we clear the stack
        } else if (strstr(comanda, "INSERT_RIGHT") != NULL) {
            INSERT_RIGHT(deget, *(comanda + SIZE_IR));
        } else if (strstr(comanda, "INSERT_LEFT") != NULL) {
            INSERT_LEFT(deget, *(comanda + SIZE_IL), output);
        } else if (strstr(comanda, "CHAR") != NULL) {
            if (strstr(comanda, "LEFT") != NULL) {
                MOVE_LEFT_CHAR(deget, *(comanda + SIZE_MLC), output);
            } else {
                MOVE_RIGHT_CHAR(deget, *(comanda + SIZE_MRC));
            }
        }

    } else if (codComanda == 3) {
        if (strstr(comanda, "LEFT") != NULL) {
            MOVE_LEFT(deget);
            push(undo, comanda);
        } else {
            MOVE_RIGHT(deget);
            push(undo, comanda);
        }
    }
    eliminaComanda(coadaComenzi);
}

void elibereazaCoada(TComenzi *c) { // free the memory allocated for the queue
    TListaCom aux;
    while (c->inceput != NULL) {
        aux = c->inceput;
        c->inceput = aux->next;
        free(aux->info);
        free(aux);
    }
    free(c);
}