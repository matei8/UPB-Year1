/* POPESCU Matei 315CB*/
#include <stdio.h>
#include <stdlib.h>
#include "Banda.h"

TCelula alocCelula(char valoare) { //initializare celula din banda
    TCelula celula = (TCelula)malloc(sizeof(TCelula));
    if (celula == NULL) {
        return NULL;
    }
    celula->info = valoare;
    celula->urm = NULL;
    celula->prev = NULL;
    return celula;
}

TBanda initBanda() { //initializare banda
    TBanda banda = (TBanda)malloc(sizeof(TCelula));
    if (banda == NULL) {
        return NULL;
    }
    banda->santinela = alocCelula(0);
    banda->deget = banda->santinela;
    return banda;
}

/* Mai jos sunt implementate toate functiile de upddate si query */

void WRITE(TCelula *deget, char val) {
    (*deget)->info = val;
}

void MOVE_LEFT_CHAR(TCelula *deget, char val, FILE *output) {
    TCelula aux = (*deget);
    while (aux->info != val) { //itereaza prin banda pana la gasirea elementului dorit
        if (aux->prev == NULL) { //daca nu a fost gasit elementul si s-a gasit NULL, se afiseaza eroare si se iese din bucla
            fprintf(output, "%s\n", "ERROR");
            return;
        }
        aux = aux->prev;
    }
    (*deget) = aux; //degetul se muta pe noua pozitie (pe elementul gasit daca exista)
}

void MOVE_RIGHT_CHAR(TCelula *deget, char val) {
    TCelula aux = (*deget);
    while (aux->info != val) {
        if (aux->urm == NULL) {
            TCelula *aux2;
            (*aux2) = alocCelula('#'); //daca nu se gaseste elemntul dorit, la intalnirea NULL se insereaza o noua celula

            (*aux2)->prev = aux;
            (*aux2)->urm = NULL;
            aux->urm = (*aux2);
            aux = (*aux2);
            break;
        }
        aux = aux->urm;
    }
    (*deget) = aux; //degetul se muta pe noua pozitie (pe elementul gasit daca exista sau pe noua celula)
}

void MOVE_LEFT(TCelula *deget) {
    if ((*deget)->prev == NULL || (*deget) == NULL) {
        return;
    }
    (*deget) = (*deget)->prev;
}

void MOVE_RIGHT(TCelula *deget) {
    if ((*deget)->urm == NULL) {
        TCelula aux = (TCelula) malloc(sizeof(TCelula)); //daca elemntul din dreapta e NULL, se creeaza o celula noua
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
            fprintf(output,"|%c|", aux->info); // printarea pozitiei degetului intre bari "|deget->info|"
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

void elibereazaBanda(TBanda banda) { //functia de eliberare a memoriei folosite de banda
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