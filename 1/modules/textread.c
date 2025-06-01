#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>

static FILE *file = NULL;

int textStart( char *fileName ){
	if((file= fopen(fileName, "r"))){ 
		return 1;
	}
    return 0;
}


char *textSequenceLine( long *storeOffset ){
	
	if( storeOffset==NULL ){  
		perror("No Offset to register");
        exit(1);
    }
    if(file == NULL){
        perror("File is not opened");
        exit(1);
    }
    
	*storeOffset=ftell(file);
	
	char *storedline=NULL;
	size_t line_length=0;

	
    if(getline(&storedline, &line_length, file) == -1){ //getline aloca dinamicamente storedline
        free(storedline);
        return NULL;
    }
    
	return storedline;
}



char *textLocatedLine( long offset ){
	char *offset_line=NULL;
	size_t line_len =0;
	
    if(file == NULL){
        perror("File is not opened");
        exit(1);
    }
    
	if((fseek(file,offset,SEEK_SET))!=0){ // deslocamento de offset bytes, a partir de SEEK_SET(posiçao iniciall)
		 free(offset_line);
         return NULL;
	}

	if(getline(&offset_line, &line_len, file) == -1){
        free(offset_line);  // Liberta memória se falhou a leitura
        return NULL;
    }
	
	return offset_line;
}

void textEnd( void ){
	if(file!=NULL){
		fclose(file);
		file=NULL;
    }
}


