#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messageCode.h"

// Declaring magic numbers
#define  MAX_LENGTH 1000
#define  FORMAT_SIZE 10

// decode function
void decode(char *word, TMatrix **b, unsigned int width) {
    int value = 0, l1 = 0, c1 = 0, rest, bit;

    // We go through each character in the word to be decoded
    for(int i = 0; i < MAX_LENGTH ; i++) {
        word[i] = 0;  // Initialize word[i] to 0 to add the decoded bits (for shifting)

        // looping through each bit of the character
        for(int j = 7; j >= 0 ;j--) {
            rest = value % 3;

            // We check the remainder and the RGB components to extract the decoded bit
            if(rest == 0 && b[l1][c1].r % 2 == 1) {
                bit = 1;
            } else if(rest == 0 && b[l1][c1].r % 2 == 0) {
                bit = 0;
            } else if(rest == 1 && b[l1][c1].g % 2 == 1) {
                bit = 1;
            } else if(rest == 1 && b[l1][c1].g % 2 == 0) {
                bit = 0;
            } else if(rest == 2 && b[l1][c1].b % 2 == 1) {
                bit = 1;
            } else if(rest == 2 && b[l1][c1].b % 2 == 0) {
                bit = 0;
            }

            // Adăugăm bitul decodificat în word[i]
            word[i] = (word[i] << 1) | bit;
            value++;

            // Verificăm restul pentru a avansa în matrix
            if(rest == 2) {
                if(c1 < width - 1) {
                    c1++;
                } else {
                    c1 = 0;
                    l1++;
                }
            }
        }
    }
}

void code(TMatrix **a, unsigned int width, const char *filePaths[]) {
    FILE *message_file = fopen(filePaths[4], "r");

    char *secretMessage = malloc(MAX_LENGTH * sizeof(char));
    fgets(secretMessage, sizeof(secretMessage), message_file);

    int l, bit, rest, valoare = 0, l1, c1, i, j;
    l1 = 0;
    c1 = 0;
    l = strlen(secretMessage);

    // Parcurgem fiecare caracter din cuvântul de codificat
    for (i = 0; i < l; i++) {
        // Parcurgem fiecare bit al caracterului
        for (j = 7; j >= 0; j--) {
            rest = valoare % 3;
            bit = (secretMessage[i] >> j) % 2;

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

            // Verificăm restul pentru a avansa în matrix
            if (rest == 2) {
                if (c1 < width - 1)
                    c1++;
                else
                    c1 = 0, l1++;
            }
            valoare++;
        }
    }
}

void readAndDecode(TMatrix **image, unsigned int width) {
    // Calling the decoding function
    char *word = malloc(MAX_LENGTH * sizeof(char));
    decode(word, image, width);
    word[MAX_LENGTH] = '\0';

    // Print the secret message that has been encoded
    char *p = strchr(word, '$');
    p[0] = '\0';
    printf("%s\n", word);
    free(word);
}

void readAndCode(unsigned int max_color, unsigned int height, unsigned int width, TMatrix **a, const char *filePaths[], FILE *output) {
    // Codificarea și scrierea informațiilor în fișierul de ieșire
    if (sizeof(char) * MAX_LENGTH > height * width * 3) {
        printf("Mesajul secret este prea lung pentru a fi codificat\n");
        return;
    }

    // Apelarea functiei de codificare
    code(a, width, filePaths);

    fprintf(output, "%s\n", "P6");
    fprintf(output, "%u %u\n", width, height);
    fprintf(output, "%u\n", max_color);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fwrite(&a[i][j].r, sizeof(char), 1, output);
            fwrite(&a[i][j].g, sizeof(char), 1, output);
            fwrite(&a[i][j].b, sizeof(char), 1, output);
        }
    }
}