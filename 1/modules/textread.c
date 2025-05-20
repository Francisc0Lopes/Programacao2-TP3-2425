#include "textread.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>

static FILE *text_file = NULL;


int textStart(char *filename){
    if(text_file != NULL){
        fclose(text_file); // Fecha ficheiro anterior, se aberto
        text_file = NULL;
    }

    text_file = fopen(filename, "r");

    if (text_file == NULL) return 0; // Erro ao abrir ficheiro
    
    return 1; 
}

char *textSequenceLine(long *storeOffset){
    if(text_file == NULL)return NULL;

    long offset = ftell(text_file);
    
    if(storeOffset != NULL){
        *storeOffset = offset;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, text_file);

    if(read == -1){
        free(line);
        return NULL; // Fim de ficheiro ou erro
    }

    return line; // O utilizador é responsável por libertar esta memória
}

char *textLocatedLine(long offset){
    if(text_file == NULL) return NULL;

    if(fseek(text_file, offset, SEEK_SET) != 0){
        return NULL; // Erro ao posicionar
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read = getline(&line, &len, text_file);

    if(read == -1){
        free(line);
        return NULL; // Fim de ficheiro ou erro
    }

    return line; // O utilizador é responsável por libertar esta memória
}

void textEnd(void){
    if(text_file != NULL){
        fclose(text_file);
        text_file = NULL;
    }
}