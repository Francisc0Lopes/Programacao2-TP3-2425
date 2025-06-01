#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "wordSearch.h"
#include "wordsAll.h"

#define LINE_BUFFER 1024
#define WORD_BUFFER 256


int main(int argc, char *argv[]){
    setlocale(LC_ALL, "pt_PT.UTF-8");

    if(argc < 2){
        fprintf(stderr, "Erro argumentos\n");
        return 1;
    }

    char strsearch[WORD_BUFFER];
    
		
		while(printf("Palavra a pesquisar: "),fgets(strsearch, sizeof(strsearch), stdin)){//le do stdin
			int len = strlen(strsearch);
			if (len > 0 && strsearch[len - 1] == '\n'){ //PARA REMOVER O NEWLINE
				strsearch[len - 1] = '\0';
			}
			
			
			utf8NormAll(strsearch);//normalizar

			for (int i = 1; i < argc; i++){// Percorrer cada ficheiro
				FILE *file = fopen(argv[i], "r");
				
				if (!file) {
					fprintf(stderr, "Erro ao abrir ficheiro %s\n", argv[i]);
					continue;
				}
				
				char linha_original[LINE_BUFFER];
				char linha_normalizada[LINE_BUFFER];
				int num_linha = 0;

				while(fgets(linha_original, sizeof(linha_original), file)){//le linha a linha do ficheiro
					num_linha++;
					strncpy(linha_normalizada, linha_original, LINE_BUFFER); //copia a linha original para não estragar original
					utf8NormAll(linha_normalizada); //normaliza

					if(wordProcess(linha_normalizada, wordCheck, strsearch)){ //Caso a palavra esteja na linha
						printf("Ficheiro: %s \t Linha %d: %s", argv[i], num_linha, linha_original);
					}
				}

				fclose(file);
			}
		}

    return 0;
}

