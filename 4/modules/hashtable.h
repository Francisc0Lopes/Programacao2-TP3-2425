#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "../2/modules/vecloc.h"
#define TABLE_SIZE 1009 // número primo para melhor dispersão
#define MAX 1024

typedef struct hlNode{ // Nó de uma lista de palavras no mesmo índice da tabela
 struct hlNode *next; // ponteiros de ligação na árvore
 char *word; // string alojada dinamicamente, com a palavra associada
 VecLoc *vec; // vetor com a localização das linhas que contêm a palavra
} HLNode;

typedef struct { // Descritor de uma hash-table
 HLNode **table; // acesso à tabela de ponteiros, alojada dinamicamente
 int size; // dimensão da tabela, a definir na criação
} HTable; 

typedef struct { // Contexto para registar ocorrência de uma palavra
 HTable *tab; // endereço do descritor da tabela
 Location locData; // localização da linha, para registar nas ocorrências
} ContextHash; 

HTable *hCreate( int size ); 
void hAddWord( HTable *ht, char *data, Location *loc );
VecLoc *hFindWord( HTable *ht, char *data ); 
void hDelete( HTable *ht ); 
int wordStoreHash( char *word, void *context ); 




#endif  // HASHTABLE_H
