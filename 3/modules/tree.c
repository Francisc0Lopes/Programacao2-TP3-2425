
#include "tree.h"




void tAddWord( TNode **rootPtr, char *data, Location *loc ){


}

void tBalance(TNode **rootPtr){

} 

VecLoc *tFindWord( TNode *root, char *data ){

}

void tDelete( TNode *root ){


}

int wordStoreTree( char *word, void *context ){

    
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