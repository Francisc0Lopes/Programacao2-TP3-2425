#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modules/textread.h"

int main(int argc, char *argv[]) {
    if(argc < 2){
        fprintf(stderr, "Uso: %s <nome_ficheiro>\n", argv[0]);
        return 1;
    }

    if(!textStart(argv[1])){
        fprintf(stderr, "Erro ao abrir o ficheiro '%s'\n", argv[1]);
        return 1;
    }

    char *linha;
    long offset;

    // Leitura sequencial e impressão
    while((linha = textSequenceLine(&offset)) != NULL){
        printf("{%ld}%s", offset, linha);
        free(linha);
    }

    // Ciclo de leitura por offset
    printf("\n-- Leitura por offset --\n");
    long inputOffset;
    while(printf("> "), scanf("%ld", &inputOffset) == 1){
        char *linhaOffset = textLocatedLine(inputOffset);
        if(linhaOffset){
            printf("%s", linhaOffset);
            free(linhaOffset);
        }else{
            printf("(linha não encontrada no offset %ld)\n", inputOffset);
        }
    }

    textEnd();
    return 0;
}
