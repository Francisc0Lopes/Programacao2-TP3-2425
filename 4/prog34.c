#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules/hashtable.h"
#include "../2/modules/vecloc.h"
#include "../1/modules/textread.h"

// Função de normalização (implemente conforme a sua série anterior)
void limpa(char *str) {
    // Exemplo: converte para minúsculas e remove pontuação simples
    for (char *p = str; *p; ++p) {
        if (*p >= 'A' && *p <= 'Z') *p += 'a' - 'A';
        else if (*p < 'a' || *p > 'z') *p = ' ';
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <ficheiro1> [ficheiro2 ...]\n", argv[0]);
        return 1;
    }

    int nfiles = argc - 1;
    HTable *tab = hCreate(TABLE_SIZE);
    if (!tab) {
        fprintf(stderr, "Erro ao criar tabela hash\n");
        return 1;
    }

    // Fase 1: Construção da tabela
    for (int f = 0; f < nfiles; f++) {
        if (!textStart(argv[f + 1])) {
            fprintf(stderr, "Erro ao abrir ficheiro: %s\n", argv[f + 1]);
            continue;
        }
        long offset;
        char *line;
        int lineNum = 1;
        while ((line = textSequenceLine(&offset)) != NULL) {
            ContextHash ctx;
            ctx.tab = tab;
            ctx.locData.fileIdx = f;
            ctx.locData.line = lineNum;
            ctx.locData.offset = offset;

            // Normaliza e processa as palavras da linha
            char strcopy[MAX];
            strncpy(strcopy, line, MAX-1);
            strcopy[MAX-1] = '\0';
            free(line);

            // Normalização (implemente conforme necessário)
            limpa(strcopy);

            wordProcess(strcopy, wordStoreHash, &ctx);

            lineNum++;
        }
        textEnd();
    }

    // Fase 2: Consulta
    printf("Introduza palavras para pesquisar (Ctrl+D para terminar):\n");
    char palavra[MAX];
    while (printf("> "), fflush(stdout), scanf("%1023s", palavra) == 1) {
        limpa(palavra);
        VecLoc *vec = hFindWord(tab, palavra);
        if (!vec || vlSize(vec) == 0) {
            printf("Palavra '%s' não encontrada.\n", palavra);
            continue;
        }

        // Agrupa por ficheiro
        for (int f = 0; f < nfiles; f++) {
            int encontrou = 0;
            for (int i = 0; i < vlSize(vec); i++) {
                Location *loc = vlGet(vec, i);
                if (loc->fileIdx == f) {
                    if (!encontrou) {
                        if (!textStart(argv[f + 1])) {
                            printf("Erro ao abrir ficheiro: %s\n", argv[f + 1]);
                            break;
                        }
                        encontrou = 1;
                    }
                    char *linha = textLocatedLine(loc->offset);
                    if (linha) {
                        printf("[%s][%d]: %s", argv[f + 1], loc->line, linha);
                        free(linha);
                    }
                }
            }
            if (encontrou) textEnd();
        }
    }

    hDelete(tab);
    return 0;
}