#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "messageCode.h"

// Declaram numerele magice utilizate
#define  lungime_maxima 1000
#define dimensiune_format 10

// Functia de decodificare
void decodifica(char cuvant2[], TMatrice **b, unsigned int lungime_cuvant, unsigned int latime) {
    int valoare = 0,l1 = 0, c1 = 0, rest,bit,i,j;

    // Parcurgem fiecare caracter din cuvântul de decodificat
    for(i = 0; i < lungime_cuvant ;i++) {
        cuvant2[i] = 0;  // Inițializează cuvant2[i] cu 0 pentru a adăuga biții decodificați

        // Parcurgem fiecare bit al caracterului
        for(j = 7; j >= 0 ;j--) {
            rest = valoare % 3;

            // Verificăm restul și componentele RGB pentru a extrage bitul decodificat
            if(rest == 0 && b[l1][c1].r % 2 == 1)
                bit = 1;
            else if(rest == 0 && b[l1][c1].r % 2 == 0)
                bit = 0;
            else if(rest == 1 && b[l1][c1].g % 2 == 1)
                bit = 1;
            else if(rest == 1 && b[l1][c1].g % 2 == 0)
                bit = 0;
            else if(rest == 2 && b[l1][c1].b % 2 == 1)
                bit = 1;
            else if(rest == 2 && b[l1][c1].b % 2 == 0)
                bit = 0;

            // Adăugăm bitul decodificat în cuvant2[i]
            cuvant2[i] = (cuvant2[i] << 1) | bit;
            valoare++;

            // Verificăm restul pentru a avansa în matrice
            if(rest == 2) {
                if(c1 < latime-1) {
                    c1++;
                } else {
                    c1 = 0;
                    l1++;
                }
            }
        }
    }
}

void code(TMatrice **a, unsigned int latime, const char *filePaths[]) {
    FILE *message_file = fopen(filePaths[4], "r");

    char cuvant[lungime_maxima];
    fgets(cuvant, sizeof(cuvant), message_file);
    int l, bit, rest, valoare = 0, l1, c1, i, j;
    l1 = 0;
    c1 = 0;
    l = strlen(cuvant);

    // Parcurgem fiecare caracter din cuvântul de codificat
    for (i = 0; i < l; i++) {
        // Parcurgem fiecare bit al caracterului
        for (j = 7; j >= 0; j--) {
            rest = valoare % 3;
            bit = (cuvant[i] >> j) % 2;

            // Verificăm restul și bitul pentru a modifica componentele RGB
            if (rest == 0) {
                if (bit == 0 && a[l1][c1].r % 2 == 1)
                    a[l1][c1].r--;
                else if (bit == 1 && a[l1][c1].r % 2 == 0)
                    a[l1][c1].r++;
            } else if (rest == 1) {
                if (bit == 0 && a[l1][c1].g % 2 == 1)
                    a[l1][c1].g--;
                else if (bit == 1 && a[l1][c1].g % 2 == 0)
                    a[l1][c1].g++;
            } else {
                if (bit == 0 && a[l1][c1].b % 2 == 1)
                    a[l1][c1].b--;
                else if (bit == 1 && a[l1][c1].b % 2 == 0)
                    a[l1][c1].b++;
            }

            // Verificăm restul pentru a avansa în matrice
            if (rest == 2) {
                if (c1 < latime - 1)
                    c1++;
                else
                    c1 = 0, l1++;
            }
            valoare++;
        }
    }
}