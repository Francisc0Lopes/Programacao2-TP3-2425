#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../1/modules/textread.h"
#include "modules/vecloc.h"

#define MAX_FILES 100

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file1> [file2 ...]\n", argv[0]);
        return 1;
    }

    int nfiles = argc - 1;
    VecLoc **vecs = (VecLoc **)malloc(nfiles * sizeof(VecLoc *));
    if (!vecs) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    // Fase 1: Ler todos os ficheiros e guardar localizações
    for (int i = 0; i < nfiles; i++) {
        if (!textStart(argv[i + 1])) {
            fprintf(stderr, "Error opening file: %s\n", argv[i + 1]);
            vecs[i] = NULL;
            continue;
        }
        vecs[i] = vlCreate();
        if (!vecs[i]) {
            fprintf(stderr, "Memory allocation error for VecLoc\n");
            textEnd();
            continue;
        }
        long offset;
        char *line;
        int lineNum = 1;
        while ((line = textSequenceLine(&offset)) != NULL) {
            Location loc = {i, lineNum, offset};
            vlAdd(vecs[i], &loc);
            lineNum++;
            free(line);
        }
        textEnd();
    }

    // Fase 2: Ciclo de consulta
    printf("Enter <fileIdx> <lineNum> (Ctrl-D to end):\n");
    int fileIdx, lineNum;
    while (printf("> "), fflush(stdout), scanf("%d %d", &fileIdx, &lineNum) == 2) {
        if (fileIdx < 0 || fileIdx >= nfiles || !vecs[fileIdx]) {
            printf("Invalid file index.\n");
            continue;
        }
        if (lineNum <= 0 || lineNum > vlSize(vecs[fileIdx])) {
            printf("Invalid line number.\n");
            continue;
        }
        Location *loc = vlGet(vecs[fileIdx], lineNum - 1);
        if (!loc) {
            printf("Location not found.\n");
            continue;
        }
        if (!textStart(argv[fileIdx + 1])) {
            printf("Error opening file: %s\n", argv[fileIdx + 1]);
            continue;
        }
        char *line = textLocatedLine(loc->offset);
        if (line) {
            printf("[%s][%d]: %s", argv[fileIdx + 1], lineNum, line);
            free(line);
        } else {
            printf("Line not found.\n");
        }
        textEnd();
    }

    // Libertar memória
    for (int i = 0; i < nfiles; i++) {
        if (vecs[i]) vlDelete(vecs[i]);
    }
    free(vecs);

    return 0;
}