#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#include "messageCode.h"
#include "comands.h"

// Declaring magic numbers
#define  MAX_LENGTH 1000
#define  FORMAT_SIZE 10

void printHelpMenu() {
    printf("Command syntax: ./steg [-option_name]... [arguments]\n\n");
    printf("----------------------Available File formats-----------------------\n");
    printf("\t\t\tPPM -with P6 header\n");
    printf("\n");
    printf("----------------------------Options--------------------------------\n");
    printf("\t  -h print help menu\n");
    printf("\t  -c code message\n");
    printf("\t  -d decode message\n");
    printf("\t  -t print timestamp when the file was modified\n");
    printf("\t  -l create log file with the time of the current files\n");
    printf("\t  -lc clear log file\n");
    printf("\t  -s print size of input and output files\n");
    printf("\n");
    printf("-------------------------Options Syntax----------------------------\n");
    printf("\t  -c [input_file] [output_file] [message_file]\n");
    printf("\t  -d [input_file]\n");
    printf("\t  -t [file1] [file2]\n");
    printf("\t  -l [log_file] [file1] [file2]\n");
    printf("\t  -lc [log_file]\n");
    printf("\t  -s [file1] [file2]\n");
    printf("\n");

}

void timestamp(const char *filePath) { // print the time a file was modified at
    struct stat attrib;
    stat(filePath, &attrib);
    char date[10];

    strftime(date, 10, "%d-%m-%y", gmtime(&(attrib.st_ctime)));
    printf("The file %s was last modified at %s\n", filePath, date);
    date[0] = 0;
}

void logChanges(FILE *log, const char *files[]) { // write to log file time of changes to the original file
    struct stat attrib;

    stat(files[3], &attrib);
    char date[10];

    strftime(date, 10, "%d-%m-%y", gmtime(&(attrib.st_ctime)));
    fprintf(log, "File %s was modified at: %s\n", files[3], date);

    stat(files[4], &attrib);
    strftime(date, 10, "%d-%m-%y", gmtime(&(attrib.st_ctime)));
    fprintf(log, "File %s was modified at: %s\n", files[4], date);

    fclose(log);
}

void clearLog(FILE *log) { // erase contents of log file
    fprintf(log, "%s", "");
    fclose(log);
}

void getFileSize(const char *filePaths[]) {
    FILE *input = fopen(filePaths[2], "r");
    fseek(input, 0L, SEEK_END);
    long int size1 = ftell(input);
    printf("Size of input file: %ld\n", size1);
    fclose(input);

    FILE *output = fopen(filePaths[3], "r");
    fseek(output, 0L, SEEK_END);
    long int size2 = ftell(output);
    printf("Size of output file: %ld\n", size2);
    fclose(output);
}

void executeCommand(const char *command, const char *filePaths[]) {
    if (strcmp(command, "-t") == 0) {
        timestamp(filePaths[2]);
        return;
    } else if (strcmp(command, "-l") == 0) {
        FILE *log = fopen(filePaths[2], "aw");
        logChanges(log, filePaths);
        return;
    } else if (strcmp(command, "-lc") == 0) {
        FILE *log = fopen(filePaths[2], "w");
        clearLog(log);
        return;
    } else if (strcmp(command, "-s") == 0) {
        getFileSize(filePaths);
        return;
    } else if (strcmp(command, "-d") == 0 || strcmp(command, "-c") == 0) {
        // Opening files
        FILE *input, *output, *secret_message;
        char *word = malloc(MAX_LENGTH * sizeof(char));
        input = fopen(filePaths[2], "rb");

        unsigned int width, height, max_color;
        unsigned char red, green, blue;
        char format[FORMAT_SIZE];

        // Get PPM file parameters info
        fscanf(input, "%s", format);
        fscanf(input, "%u", &width);
        fscanf(input, "%u", &height);
        fscanf(input, "%u", &max_color); // max value for color

        char newline_buffer = '\n';
        fscanf(input, "%c", &newline_buffer);

        TMatrix **image = (TMatrix **) malloc(height * sizeof(TMatrix*));
        if (image == NULL)
            return;

        for (int i = 0; i < height; i++) {
            image[i] = (TMatrix *) malloc(width * sizeof(TMatrix));
            if (image[i] == NULL)
                return;
        }

        // Reading the pixel array from the input file
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                fread(&red, sizeof(char), 1, input);
                fread(&green, sizeof(char), 1, input);
                fread(&blue, sizeof(char), 1, input);

                image[i][j].r = red;
                image[i][j].g = green;
                image[i][j].b = blue;
            }
        }

        if (strcmp(command, "-d") == 0) {
             readAndDecode(image, width);
        } else {
            printf("\t\t    !!!Warning!!!\n\tThe message to be encoded must end in '$' \n");
            output = fopen(filePaths[3], "wb");
            secret_message = fopen(filePaths[4], "rt");
            fgets(word, sizeof(word), secret_message);  //textul de codificat

            readAndCode(max_color, height, width, image, filePaths, output);
            fclose(output);
            fclose(secret_message);
        }
        // Free the memory allocated for the Pixel Image
        for (unsigned int i = 0; i < height; i++) {
            free(image[i]);
        }
        free(image);
        fclose(input);
    }
}