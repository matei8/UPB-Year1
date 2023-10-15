#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "messageCode.h"

// Declaring magic numbers
#define  MAX_LENGTH 1000
#define  FORMAT_SIZE 10

// decode function
void decode(char word[], TMatrix **imageMatrix, unsigned int width) {
    int bitNumber = 0, l_count = 0, c_count = 0, reminder, bit;
    // l_count = line count/current line
    // c_count = column count/current column

    // We go through each character in the word to be decoded
    for(int i = 0; i < MAX_LENGTH ; i++) {
        word[i] = 1;  // Initialize word[i] to 0 to add the decoded bits (for shifting)

        // looping through each bit of the character
        for(int j = 7; j >= 0; j--) {
            reminder = bitNumber % 3;

            // We check the remainder and the RGB components to extract the decoded bit
            int red_factor = (reminder == 0 && imageMatrix[l_count][c_count].r % 2 == 1);
            int green_factor = (reminder == 1 && imageMatrix[l_count][c_count].g % 2 == 1);
            int blue_factor = (reminder == 2 && imageMatrix[l_count][c_count].b % 2 == 1);

            if(red_factor || green_factor || blue_factor) {
                bit = 1;
            } else {
                bit = 0;
            }

            // Adding the decoded bit to word[i]
            word[i] = (word[i] << 1) | bit;
            bitNumber++;

            // Check the reminder in order to proceed through the matrix
            if(reminder == 2) {
                if(c_count < width - 1) {
                    c_count++;
                } else {
                    c_count = 0;
                    l_count++;
                }
            }
        }
    }
}

void code(TMatrix **imageMatrix, unsigned int width, const char *filePaths[]) {
    FILE *message_file = fopen(filePaths[4], "r");

    char secretMessage[MAX_LENGTH];
    fgets(secretMessage, sizeof(secretMessage), message_file);

    int bit, reminder, bitNumber = 0, l_count, c_count;
    // l_count = line count/current line
    // c_count = column count/current column
    l_count = 0;
    c_count = 0;

    // We go through every character from the secretMessage
    for (int i = 0; i < strlen(secretMessage); i++) {
        // Analyzing every bit of the current character
        for (int j = 7; j >= 0; j--) {
            reminder = bitNumber % 3;
            bit = (secretMessage[i] >> j) % 2;

            // Check the reminder for setting the bits in the RGB values
            if (reminder == 0) { // checking for red
                if (bit == 0 && imageMatrix[l_count][c_count].r % 2 == 1)
                    imageMatrix[l_count][c_count].r--;
                else if (bit == 1 && imageMatrix[l_count][c_count].r % 2 == 0)
                    imageMatrix[l_count][c_count].r++;

            } else if (reminder == 1) { // checking for green
                if (bit == 0 && imageMatrix[l_count][c_count].g % 2 == 1)
                    imageMatrix[l_count][c_count].g--;
                else if (bit == 1 && imageMatrix[l_count][c_count].g % 2 == 0)
                    imageMatrix[l_count][c_count].g++;

            } else { // checking for blue (the reminder is 2)
                if (bit == 0 && imageMatrix[l_count][c_count].b % 2 == 1)
                    imageMatrix[l_count][c_count].b--;
                else if (bit == 1 && imageMatrix[l_count][c_count].b % 2 == 0)
                    imageMatrix[l_count][c_count].b++;
            }

            // Checking that we don't exceed the image boundaries
            // If yes =====> Segmentation Fault
            if (reminder == 2) {
                if (c_count < width - 1)
                    c_count++;
                else
                    c_count = 0, l_count++;
            }
            bitNumber++;
        }
    }
    fclose(message_file);
}

void readAndDecode(TMatrix **image, unsigned int width) {
    // Calling the decoding function
    char *word = malloc(MAX_LENGTH * sizeof(char));
    decode(word, image, width);

    // Print the secret message that has been encoded
    char *p = strchr(word, '$');
    p[0] = '\0';
    printf("The secret message is: \"%s\"\n", word);
    free(word);
}

// Reading from the text file to get the secret message and code it in to the output file
void readAndCode(unsigned int max_color, unsigned int height, unsigned int width, TMatrix **a, const char *filePaths[], FILE *output) {
    if (sizeof(char) * MAX_LENGTH > height * width * 3) {
        printf("The message is too long to be coded!!!\nTry a shorter message\n");
        return;
    }

    // Coding the message into the image
    code(a, width, filePaths);

    // Writing the header of the PPM file
    fprintf(output, "%s\n", "P6");
    fprintf(output, "%u %u\n", width, height);
    fprintf(output, "%u\n", max_color);

    // Writing the image to the file, below the header
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            fwrite(&a[i][j].r, sizeof(char), 1, output);
            fwrite(&a[i][j].g, sizeof(char), 1, output);
            fwrite(&a[i][j].b, sizeof(char), 1, output);
        }
    }
}