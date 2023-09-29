#ifndef STEGANOGRAPHYONIMAGES_MESSAGECODE_H
#define STEGANOGRAPHYONIMAGES_MESSAGECODE_H

typedef struct matrice {
    unsigned char r, g, b;
} TMatrice;

void decodifica(char cuvant2[], TMatrice **b, unsigned int lungime_cuvant, unsigned int latime);
void code(TMatrice **a, unsigned int latime, const char *filePaths[]);

#endif //STEGANOGRAPHYONIMAGES_MESSAGECODE_H
