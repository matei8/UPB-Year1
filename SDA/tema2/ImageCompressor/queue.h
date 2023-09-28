#include <stdio.h>

#include "tree.h"

#ifndef TEMA2_QUEUE_H
#define TEMA2_QUEUE_H

typedef struct celula {
    QuadTree info;
    struct celula *next;
} TCell, *TList;

typedef struct queue {
    TList start, end;
} TQueue;

#endif // TEMA2_QUEUE_H
