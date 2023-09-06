/*POPESCU Matei-315CB*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "antet_functii.h"

TPCelula initCelula(int nod, int cost_arc, char *locatie) {
    TPCelula aux = calloc(1, sizeof(TCelula));
    aux->next = NULL;
    aux->nod = nod;
    aux->cost_arc = cost_arc;
    aux->locatie = calloc(20, sizeof(char));
    strcpy(aux->locatie, locatie);
    return aux;
}

TGraf *initGraf(int size) {
    TGraf *g = calloc(1, sizeof(TGraf));
    if (g == NULL) {
        return NULL;
    }

    g->size = size;
    g->adj_list = calloc(size, sizeof(TCelula));
    for (int i = 0; i < size; i++) {
        g->adj_list[i] = calloc(1, sizeof(TCelula));
    }
    return g;
}

void setLocationsIdxs(FILE *input, char *locatii[], int size) {
    for (int i = 0; i < size; i++) {
        locatii[i] = calloc(20, sizeof(char));
        char *locatie = calloc(20, sizeof(char));

        fscanf(input, "%s", locatie);
        if (locatie[0] < 65) {
            int arc = locatie[0] - '0';
            i--;
            free(locatie);
            continue;
        }
        int gasit = 0;
        for (int j = 0; j < i; j++) {
            if (strcmp(locatie, locatii[j]) == 0) {
                gasit = 1;
                break;
            }
        }

        if(gasit == 0) {
            strcpy(locatii[i], locatie);
        } else {
            i--;
        }
        free(locatie);
    }
}

int getLocationIdx(char *location, char *locations[], int size) {
    int idx = 0;
    for (int i = 0; i < size; i++) {
        if(strcmp(location, locations[i]) == 0) {
            idx = i;
            break;
        }
    }
    return idx;
}

void getAdjList(FILE *input, TGraf *g, char *locatii[], int size) {
    if (input == NULL) {
        return ;
    }

    char *start = calloc(20, sizeof(char));
    char *finish = calloc(20, sizeof(char));
    int cost;

    while (fscanf(input, "%s%s%d", start, finish, &cost) != EOF) {
        int startIdx = getLocationIdx(start, locatii, size);
        int finIdx = getLocationIdx(finish, locatii, size);

        if (g->adj_list[startIdx]->locatie == NULL && g->adj_list[finIdx]->locatie == NULL) {
            g->adj_list[startIdx] = initCelula(startIdx, 0, start);
            g->adj_list[startIdx]->next = (TPCelula)initCelula(finIdx, cost, finish);

            g->adj_list[finIdx] = initCelula(finIdx, 0, finish);
            g->adj_list[finIdx]->next = (TPCelula)initCelula(startIdx, cost, start);

        } else if (g->adj_list[startIdx]->locatie == NULL) {
            g->adj_list[startIdx] = initCelula(startIdx, 0, start);
            g->adj_list[startIdx]->next = (TPCelula)initCelula(finIdx, cost, finish);

            TPCelula aux2 = g->adj_list[finIdx];
            while (aux2->next != NULL) {
                aux2 = aux2->next;
            }
            aux2->next = (TPCelula)initCelula(startIdx, cost, start);

        } else if (g->adj_list[finIdx]->locatie == NULL) {
            g->adj_list[finIdx] = initCelula(finIdx, 0, finish);
            g->adj_list[finIdx]->next = (TPCelula)initCelula(startIdx, cost, start);

            TPCelula aux = g->adj_list[startIdx];
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = (TPCelula)initCelula(finIdx, cost, finish);

        } else {
            TPCelula aux = g->adj_list[startIdx];
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = (TPCelula)initCelula(finIdx, cost, finish);

            TPCelula aux2 = g->adj_list[finIdx];
            while (aux2->next != NULL) {
                aux2 = aux2->next;
            }
            aux2->next = (TPCelula)initCelula(startIdx, cost, start);
        }
    }
    free(start);
    free(finish);
}

int DFS(TGraf *g) {
    TPCelula list = g->adj_list[0];
    int componente = 0, frecv[g->size], idx = 0;
    for (int i = 0; i < g->size; i++) {
        frecv[i] = 0;
    }

    while (idx != g->size) {
        if (frecv[idx] == 0 && frecv[list->next->nod] == 0) {
            componente++;
        }
        frecv[idx] = 1;
        while (list->next != NULL) {
            list = list->next;
            if (frecv[list->nod] == 0) {
                frecv[list->nod] = 1;
            }
        }
        idx++;
        if (idx < g->size - 1) {
            list = g->adj_list[idx];
        } else {
            break;
        }
    }
    return componente;
}

int comparaLaturi(const void *a, const void *b) { // functie de comparare pentru qsort
    TLatura *lat1 = (TLatura *)a;
    TLatura *lat2 = (TLatura *)b;
    return lat1->cost - lat2->cost;
}

TLatura *vectorLaturi(TGraf *g, int nr_laturi) {
    TLatura *v = calloc(nr_laturi, sizeof(TLatura));
    int idx_latura = 0, *frecv = calloc(g->size, sizeof(int));

    for (int i = 0; i < g->size; i++) {
        frecv[i] = 0;
    }

    for (int i = 0; i < g->size; i++) {
        TPCelula aux = g->adj_list[i];
        aux = aux->next;
        while (aux != NULL) {
            if (frecv[aux->nod] == 0 || g->adj_list[i]->nod < aux->nod) {
                v[idx_latura].sursa = g->adj_list[i]->nod;
                v[idx_latura].destinatie = aux->nod;
                v[idx_latura].cost = aux->cost_arc;
                idx_latura++;
                frecv[aux->nod] = 1;
            }
            aux = aux->next;
        }
        frecv[g->adj_list[i]->nod] = 1;
    }

    qsort(v, nr_laturi, sizeof(TLatura), comparaLaturi);

    free(frecv);
    return v;
}

int comparaComp(const void *a, const void *b) { // functie de comparare pentru qsort
    TComponenta *comp1 = (TComponenta *)a;
    TComponenta *comp2 = (TComponenta *)b;
    return comp1->cost - comp2->cost;
}

TComponenta *costuriComponente(TLatura *v, int nrNoduri, int nrLaturi, int nrComp) {
    TComponenta *costuri = calloc(nrComp, sizeof(TComponenta));
    int *comp = calloc(nrNoduri, sizeof(int));
    int *cost = calloc(nrNoduri, sizeof(int));

    for (int i = 0; i < nrNoduri; i++) {
        comp[i] = cost[i] = -1;
    }

    for (int i = 0; i < nrLaturi; i++) {
        if (comp[v[i].sursa] != -1 && comp[v[i].destinatie] == -1) {
            comp[v[i].destinatie] = comp[v[i].sursa];
            int cost_curent = cost[v[i].sursa] + v[i].cost;
            for (int j = 0; j < nrNoduri; j++) {
                if (comp[j] == comp[v[i].sursa]) {
                    cost[j] = cost_curent;
                }
            }
        } else if (comp[v[i].sursa] == -1 && comp[v[i].destinatie] != -1) {
            comp[v[i].sursa] = comp[v[i].destinatie];
            int cost_curent = cost[v[i].destinatie] + v[i].cost;
            for (int j = 0; j < nrNoduri; j++) {
                if (comp[j] == comp[v[i].destinatie]) {
                    cost[j] = cost_curent;
                }
            }
        } else if (comp[v[i].sursa] != -1 && comp[v[i].destinatie] != -1) {
            if (comp[v[i].sursa] != comp[v[i].destinatie]) {
                int cost_curent = cost[v[i].sursa] + cost[v[i].destinatie] + v[i].cost;
                int comp_aux = comp[v[i].destinatie];
                for (int j = 0; j < nrNoduri; j++) {
                    if (comp[j] == comp_aux) {
                        comp[j] = comp[v[i].sursa];
                        cost[j] = cost_curent;
                    } else if (comp[j] == comp[v[i].sursa]) {
                        cost[j] = cost_curent;
                    }
                }
            }
        } else {
            comp[v[i].sursa] = comp[v[i].destinatie] = v[i].sursa;
            cost[v[i].sursa] = cost[v[i].destinatie] = v[i].cost;
        }
    }

    int comp_curenta = -1, idx = 0;
    for (int i = 0; i < nrNoduri; i++) {
        if (comp_curenta != comp[i]) {
            int check = 0;
            for (int j = 0; j < nrComp; j++) {
                if (costuri[i].nrComp == comp_curenta) {
                    check = 1;
                    break;
                }
            }
            if (check == 0) {
                comp_curenta = comp[i];
                costuri[idx].nrComp = comp_curenta;
                costuri[idx].cost = cost[i];
                idx++;
            }
        }
        if (idx == nrComp) {
            break;
        }
    }

    qsort(costuri, nrComp, sizeof(TComponenta), comparaComp);

    free(comp);
    free(cost);
    return costuri;
}