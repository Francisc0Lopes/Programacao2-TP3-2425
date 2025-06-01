#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../1/modules/textread.h"
#include "./modules/tree.h"
#include "./modules/allFuncs.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Uso: %s ficheiro1 [ficheiro2 ...]\n", argv[0]);
        return 1;
    }

    TNode *root = NULL;

    // === Fase 1: construir árvore com palavras e localizações ===
    for(int f = 1; f < argc; f++){
        if(!textStart(argv[f])){
            fprintf(stderr, "Erro ao abrir ficheiro: %s\n", argv[f]);
            continue;
        }

        char *linha;
        long offset;
        int numLinha = 1;

        while((linha = textSequenceLine(&offset)) != NULL){
            char linhaNormalizada[MAX];
            strncpy(linhaNormalizada, linha, MAX);
            linhaNormalizada[MAX - 1] = '\0';

            utf8NormAll(linhaNormalizada);

            ContextTree ctx;
            ctx.rootPtr = &root;
            ctx.locData.fileIdx = f;
            ctx.locData.line = numLinha;
            ctx.locData.offset = offset;

            wordProcess(linhaNormalizada, wordStoreTree, &ctx);

            free(linha);
            numLinha++;
        }

        textEnd();
    }

    // Balancear a árvore
    tBalance(&root);

    // === Fase 2: interação com o utilizador ===
    char palavra[MAX];
    printf("\nIntroduza palavras a pesquisar (Ctrl-D para terminar):\n");


    while(fgets(palavra, MAX, stdin)){
        palavra[strcspn(palavra, "\n")] = '\0';  // remover newline


        utf8NormAll(palavra);
        VecLoc *v = tFindWord(root, palavra);

        if(!v || vlSize(v) == 0){
            printf("Palavra não encontrada.\n\n");
            continue;
        }

        int lastFile = -1;

        printf("\nResultado pesquisa:\n");
        for(int i = 0; i < vlSize(v); i++){
            Location *loc = vlGet(v, i);
            if(loc->fileIdx != lastFile){
                if(lastFile != -1) textEnd();
                if(!textStart(argv[loc->fileIdx])){
                    fprintf(stderr, "Erro ao abrir ficheiro.\n");
                    continue;
                }
                lastFile = loc->fileIdx;
            }

            char *linhaOriginal = textLocatedLine(loc->offset);
            if(linhaOriginal){
                printf("%s: linha %d: %s\n", argv[loc->fileIdx], loc->line, linhaOriginal);
                free(linhaOriginal);
            }
        }

        if(lastFile != -1) textEnd();

        printf("\n");
    }

    // === Fim: libertar memória ===
    tDelete(root);
    return 0;
}
