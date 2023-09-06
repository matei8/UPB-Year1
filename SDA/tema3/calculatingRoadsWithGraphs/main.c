/*POPESCU Matei-315CB*/

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "antet_functii.h"
int main(int argc, const char *argv[]) {
    int cerinta;
    cerinta = atoi(argv[1]);
    FILE *output;
    FILE *input;
    output = fopen("tema3.out", "w");
    input = fopen("tema3.in", "r");

    int size, nr_drumuri;
    fscanf(input, "%d", &size);
    fscanf(input, "%d", &nr_drumuri);

    char *locatii[size]; // vector de locatii pentru indexarea stringurilor citite din input
    setLocationsIdxs(input, locatii, size); // faciliteaza manevrabilitatea datelor

    fclose(input); // close file
    input = fopen("tema3.in", "r"); // reopen the file to reset the file pointer and read again from file

    fscanf(input, "%d", &size); // read these values again
    fscanf(input, "%d", &nr_drumuri);

    TGraf *g = initGraf(size); // initializeaza graf
    getAdjList(input, g, locatii, size); // creeaza lista de adiacenta

    int nrComponente = DFS(g); // calculeaza numarul  de componente conexe

    fprintf(output, "%d\n", nrComponente);
    TLatura *laturi = vectorLaturi(g, nr_drumuri); // creeaza un vector de laturi (sursa, dest, cost)

    TComponenta *costuri = costuriComponente(laturi, g->size, nr_drumuri, nrComponente);

    for (int i = 0; i < nrComponente; i++) {
        fprintf(output, "%d\n", costuri[i].cost);
    }

    // close the files and free memory
    for (int i = 0; i < g->size; i++) {
        free(locatii[i]); // dezaloc vectorul de locatii
    }

    TPCelula aux, prev;
    for (int i = 0; i < g->size; i++) {
        aux = g->adj_list[i];
        while (aux) {
            prev = aux;
            aux = aux->next;
            free(prev->locatie);
            free(prev);
        }
    }
    free(g->adj_list);
    printf("%d\n", g->size);
    for (int i = 0; i < g->size; i++) {
        if (g->adj_list == NULL)
            printf("%d\n", i);
    }
    free(g);
    g = NULL;

    free(costuri);
    free(laturi);

    fclose(input);
    fclose(output);
    return 0;
}
