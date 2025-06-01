#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "wordsAll.h"



enum ClassId utf8Class(char c) {
    if ((c & 0x80) == 0) {  
        return S_ASC;
    } else if ((c & 0xC0) == 0xC0) {  
        return S_INIT;
    } else { 
        return S_CONT;
    }
}

void limpa(char *str){ //para tirar o hifen inicial e final
    int len = strlen(str);
	if(str[0] == '-'){
		for (int i = 0; i < len; i++) { //remove o hifen inicial
			str[i] = str[i + 1];  //Cada caracter 1 posição para trás
        }
        len--; 
    }
    if(len > 0 && str[len - 1] == '-'){    // Remove hífen final
        str[len - 1] = '\0'; 
    }
}

int utf8NormFirst(char str[]) {
    enum ClassId class = utf8Class(str[0]);
    int length = 1;

    if (class == S_CONT) {
        str[0] = ' ';
        return 1;
    }
    //if (str[0] == '-') {
        // Sempre substitui hífen por espaço, independente da posição
      //  str[0] = ' ';
        //return 1;
    //}


    if (class == S_INIT) {
        if ((unsigned char)str[0] == 0xC3) {
            length = 2;
            if ((unsigned char)str[1] < 0xA0) {
                str[1] += 0x20;
            }
        } else {
            str[0] = ' ';
            if (utf8Class(str[1]) == S_CONT) {
                str[1] = ' ';
                length = 2;
             }
        }
    } else if (class == S_ASC && str[0]!='-') {
        if (!isalnum(str[0]) ){
            str[0] = ' ';
        } else {
            str[0] = tolower(str[0]);
        }
    }

    return length;
}


void utf8NormAll(char str[]) {
 
    for(int i =0; str[i]!= '\0';){
		int length=utf8NormFirst(&str[i]);
		i+=length;
	} 
}




int wordProcess( char *str, int (*action)( char *word, void *context ),void *context ){
	
int count=0;
char strcopy[MAX];
strcpy(strcopy,str);

char *token = strtok(strcopy," \t\n");

	while(token!=NULL){
		limpa(token);
		count+=action(token,context);
		token=strtok(NULL," \t\n");
	}
		return count;
}

int wordPrint( char *word, void *context ){
	FILE *out = (FILE*)context;
	fprintf(out,"%s ",word);
	
	return 1;
}
