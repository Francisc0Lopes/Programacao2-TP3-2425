#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../1/modules/textread.h"
#include "modules/vecloc.h"

int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(stderr, "Uso: %s ficheiro1 [ficheiro2 ...]\n", argv[0]);
        return 1;
    }

    VecLoc *vec = vlCreate();

    if(!vec){
        fprintf(stderr, "Erro a criar vetor de localizações.\n");
        return 1;
    }

    // Fase 1: leitura de ficheiros
    for(int f = 1; f < argc; f++){
        if(!textStart(argv[f])){
            fprintf(stderr, "Erro ao abrir ficheiro: %s\n", argv[f]);
            continue;
        }
        char *linha;
        long offset;
        int numLinha = 1;

        while((linha = textSequenceLine(&offset)) != NULL){
            Location loc;
            loc.fileIdx = f;
            loc.line = numLinha++;
            loc.offset = offset;
            vlAdd(vec, &loc);
            free(linha); // responsabilidade do utilizador
        }

        textEnd();
    }



    // Fase 2: interação com o utilizador
    int fileIdx, lineNum;
    printf("Introduza pares fileIdx lineNum (Ctrl-D para terminar):\n");

    while(scanf("%d %d", &fileIdx, &lineNum) == 2){
		if(fileIdx <= 0 || fileIdx >= argc){
            fprintf(stderr, "fileIdx %d fora do intervalo.\n", fileIdx);
            continue;
        }

        for(int i = 0; i < vlSize(vec); i++){
            Location *loc = vlGet(vec, i);
            
            
            if(loc->fileIdx == fileIdx && loc->line == lineNum){

                if(!textStart(argv[fileIdx])){
                    fprintf(stderr, "Erro ao abrir ficheiro.\n");
                    break;
                }
               
                char *linha = textLocatedLine(loc->offset);

                if(linha){
                    printf("%s\n", linha);
                    free(linha);
                }
                
                textEnd();
                break;
            }
        
        }
    }

    // Libertar memória
    vlDelete(vec);
    return 0;
}
