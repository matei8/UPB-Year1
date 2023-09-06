/* POPESCU Matei 315CB*/
#include "Banda.h" //header banda (lista dublu inlantuita cu santinela)
#include "comenzi.h" //header queue cu comenzi
#include "UndoRedo.h" // header stive UNDO/REDO

int main() {
    //initializare banda
    TBanda banda = initBanda();
    banda->santinela->urm = alocCelula('#');
    banda->deget = banda->santinela->urm;

    // initializare coada
    TComenzi *coadaComenzi = initCoadaComenzi();

    //initializare stiva UNDO si REDO
    TStiva undo = initSivaUndoRedo();
    TStiva redo = initSivaUndoRedo();

    //citirea si analizarea comenzilor
    citesteComenzi(coadaComenzi, &(banda->deget), banda, &undo, &redo);

    //eliberarea memoriei folosite
    clearStack(&undo, &redo);
    elibereazaCoada(coadaComenzi);
    elibereazaBanda(banda);

    return 0;
}