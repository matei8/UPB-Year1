#ifndef STEGANOGRAPHYONIMAGES_MESSAGECODE_H
#define STEGANOGRAPHYONIMAGES_MESSAGECODE_H

typedef struct matrix {
    unsigned char r, g, b;
} TMatrix;

void decode(char word[], TMatrix **imageMatrix, unsigned int width);
void code(TMatrix **imageMatrix, unsigned int width, const char *filePaths[]);
void readAndDecode(TMatrix **image, unsigned int width);
void readAndCode(unsigned int max_color, unsigned int height, unsigned int width, TMatrix **a, const char *filePaths[], FILE *output);

#endif //STEGANOGRAPHYONIMAGES_MESSAGECODE_H