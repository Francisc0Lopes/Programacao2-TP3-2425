#ifndef TREE_H
#define TREE_H


typedef struct tNode{ // Nó da árvore binária de pesquisa
 struct tNode *left, *right; // ponteiros de ligação na árvore
 char *word; // string alojada dinamicamente, com a palavra associada
 VecLoc *vec; // vetor com a localização das linhas que contêm a palavra
}TNode; 

typedef struct { // Contexto para registar ocorrência de uma palavra
 TNode **rootPtr; // endereço do ponteiro raiz da árvore binária
 Location locData; // localização da linha, para registar nas ocorrências
}ContextTree; 


void tAddWord( TNode **rootPtr, char *data, Location *loc );
void tBalance(TNode **rootPtr); 
VecLoc *tFindWord( TNode *root, char *data ); 
void tDelete( TNode *root ); 

int wordStoreTree( char *word, void *context ); 


//SE2
int wordProcess( char *str, int (*action)( char *word, void *context ),void *context );



#endif //TREE_H