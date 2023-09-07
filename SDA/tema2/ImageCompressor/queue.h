#include <stdio.h>

#include "tree.h"

#ifndef TEMA2_QUEUE_H
#define TEMA2_QUEUE_H

typedef struct celula {
    TArb info;
    struct celula *next;
} TCelula, *TLista;

typedef struct queue {
    TLista start, end;
} TQueue;

#endif // TEMA2_QUEUE_H
