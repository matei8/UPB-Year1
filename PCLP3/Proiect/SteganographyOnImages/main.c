#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "comands.h"

int main(int argc, const char *argv[]) {
    if(!argv[1] || strcmp(argv[1], "-h") == 0 ) {
        printHelpMenu();
        return 0;
    }

    char *command = malloc(5 * sizeof(char));

    strcpy(command, argv[1]);

    executeCommand(command, argv);

    free(command);

    return 0;
}
