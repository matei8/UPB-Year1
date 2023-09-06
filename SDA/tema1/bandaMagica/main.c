#include "Banda.h" //header banda (doubly linked list)
#include "comenzi.h" //header for commands queue
#include "UndoRedo.h" // header UNDO/REDO stacks

int main() {
    // initialize tape
    TBanda banda = initBanda();
    banda->santinela->urm = alocCelula('#');
    banda->deget = banda->santinela->urm;

    // initialize commands queue
    TComenzi *coadaComenzi = initCoadaComenzi();

    // initialize UNDO and REDO stacks
    TStiva undo = initSivaUndoRedo();
    TStiva redo = initSivaUndoRedo();

    // reading and processing input commands
    citesteComenzi(coadaComenzi, &(banda->deget), banda, &undo, &redo);

    // memory free
    clearStack(&undo, &redo);
    elibereazaCoada(coadaComenzi);
    elibereazaBanda(banda);

    return 0;
}