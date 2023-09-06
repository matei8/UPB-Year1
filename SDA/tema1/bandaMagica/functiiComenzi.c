/* POPESCU Matei 315CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comenzi.h"
#include "Banda.h"

//lungimile comenzilor care vor fi citite ca siruri de caractere

#define SIZE_W 6
#define SIZE_IR 13
#define SIZE_IL 12
#define SIZE_MLC 15
#define SIZE_MRC 16

TComenzi *initCoadaComenzi() {
    TComenzi *c = (TComenzi *)malloc(sizeof(TComenzi));
    if(c == NULL) {
        return NULL;
    }
    c->inceput = c->sfarsit = NULL;
    return c;
}

void adaugaComanda(TComenzi *c, char *com) {
    TListaCom comanda = (TListaCom) malloc(sizeof(TListaCom));
    comanda->info = com;
    comanda->next = NULL;

    if (c->sfarsit != NULL) {
        c->sfarsit->next = comanda;
    } else {
        c->inceput = comanda;
    }

    c->sfarsit = comanda;
}

void afisareComenzi(TComenzi *c) {
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

/*functia de mai jos codifica comenzile primite ca parametru
 * in functie de functionalitatea fiecareia, clasificandu-le si
 * fiind mai usor de citit codul
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

        /* Valoarea comenzii (-1/0/1/2/3) o folosim ca sa fie mai usor de citit si implementat codul
         * de asemenea functia verificaComanda trebuie executata o singura data pentru fiecare iteratie
         */
        int codComanda = verificaComanda(comanda);

        /* Verificam fiecare comanda sa vedem daca ne cere sa scriem
         * in lista noi valori (codComanda = 0) sau DOAR ne deplasam (codComanda = 3)
         * sau trebuie executat (codComanda = 1), altfel
         * inseamna ca cm citit o comanda de UNDO/REDO (codComanda = -1).
         * Mai exista si cazul de afisat (codComanda = 2)
         * in care avem SHOW/SHOW_CURRENT
         */
        if (codComanda == 0 || codComanda == 3) {
            adaugaComanda(coadaComenzi, comanda);
        } else if (codComanda == 1) {
            EXECUTE(coadaComenzi, deget, banda, output, undo, redo);
            continue;
        } else if (codComanda == 2) {
            if (strstr(comanda, "CURRENT") != NULL) {
                SHOW_CURRENT(deget, output);
            } else {
                SHOW(banda, deget, output);
            }
        } else if (codComanda == -1) {
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
    fclose(output); //inchidem fisierel de output si input
    fclose(input);
}

void EXECUTE(TComenzi *coadaComenzi, TCelula *deget, TBanda banda, FILE *output, TStiva *undo, TStiva *redo) {
    char *comanda = coadaComenzi->inceput->info;
    int codComanda = verificaComanda(comanda);

    //comanda + SIZE -> asa luam de la coada sirului valoarea care trebuie gasita/scrisa/inserata in banda

    if (codComanda == 0) { //cautam in stringul citit comanda care trebuie executata
        if (strstr(comanda, "WRITE") != NULL) {
            WRITE(deget, *(comanda + SIZE_W));
            clearStack(undo, redo); //dupa comanda de write stergem ce se afla in stiva
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

void elibereazaCoada(TComenzi *c) { //eliberarea cozii
    TListaCom aux = c->inceput;
    while (c->inceput != NULL) {
        aux = c->inceput;
        c->inceput = aux->next;
        free(aux->info);
        free(aux);
    }
    free(c);
    c->sfarsit = NULL;
    c->inceput = NULL;
}
