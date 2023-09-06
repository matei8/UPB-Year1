/*POPESCU Matei-315CB*/

#ifndef TEMA3_STRUCTS_H
#define TEMA3_STRUCTS_H

typedef struct celula {
    char *locatie;
    int nod;
    int cost_arc;
    struct celula *next;
} TCelula, *TPCelula;

typedef struct graf {
    int size;
    TPCelula *adj_list;
} TGraf;

typedef struct latura {
    int sursa, destinatie;
    int cost;
} TLatura;

typedef struct comp {
    int nrComp;
    int cost;
} TComponenta;

#endif //TEMA3_STRUCTS_H
