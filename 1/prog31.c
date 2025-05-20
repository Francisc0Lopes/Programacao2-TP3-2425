#include <stdio.h>
#include <stdlib.h>
#include "modules/textread.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    if (textStart(filename) == 0) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return 1;
    }

    long offset;
    char *line;
    while ((line = textSequenceLine(&offset)) != NULL) {
        printf("{%ld} %s", offset, line);
        free(line);
    }

    printf("Enter offsets to read lines (Ctrl-D to end):\n");
    while (1) {
        printf("Offset: ");
        if (scanf("%ld", &offset) != 1) {
            break; // End of input
        }

        line = textLocatedLine(offset);
        if (line != NULL) {
            printf("{%ld} %s", offset, line);
            free(line);
        } else {
            printf("No line found at offset %ld\n", offset);
        }
    }

    textEnd();
    return 0;
}