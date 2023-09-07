#include <stdio.h>

#ifndef IMAGECOMPRESSOR_IMAGE_H
#define IMAGECOMPRESSOR_IMAGE_H

// structure holding the parameters of the image
typedef struct {
    FILE *input; // pointer to the file
    unsigned int width;
    unsigned int height;
    unsigned int max_size_color; // max RGB value
    unsigned int imgSize; // image size
} TImagine;

// RGB structure (for ONE pixel)
typedef struct pixel {
    unsigned char red, green, blue;
} TPixel;

#endif //IMAGECOMPRESSOR_IMAGE_H
