/*POPESCU Matei-315CB*/

#include <stdio.h>
#include "structs.h"

#ifndef TEMA3_ANTET_FUNCTII_H
#define TEMA3_ANTET_FUNCTII_H

TPCelula initCelula(int nod, int cost_arc, char *locatie);
TGraf *initGraf(int size);
void setLocationsIdxs(FILE *input, char *locatii[], int size);
void getAdjList(FILE *input, TGraf *g, char *locatii[], int size);
int DFS(TGraf *g);
TLatura *vectorLaturi(TGraf *g, int nr_laturi);
TComponenta *costuriComponente(TLatura *v, int nrNoduri, int nrLaturi, int nrComp);

#endif //TEMA3_ANTET_FUNCTII_H
