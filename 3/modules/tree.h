#ifndef TREE_H
#define TREE_H

#define INIT_ELEMS 10


//Exercicio 2, SE3

typedef struct{ // Descritor de uma localização de linha 
   int fileIdx; //   índice no array de ponteiros para os nomes dos ficheiros 
   int line;    //   número da linha no texto 
   long offset; //   posição do início da linha no ficheiro 
} Location; 
typedef struct{    // Descritor de um vetor de localizações de linhas 
   int space;      //   quantidade de elementos alojados no array dinâmico 
   int count;      //   quantidade de elementos ocupados no array dinâmico 
   Location *data; //   aponta array alojado dinamicamente 
} VecLoc;


VecLoc *vlCreate( void );
int vlAdd( VecLoc *vec, Location *loc );
int vlSize( VecLoc *vec );
Location *vlGet( VecLoc *vec, int idx );
void vlDelete( VecLoc *vec );

//Exercicio 3, SE3

typedef struct tNode{   // Nó da árvore binária de pesquisa 
struct tNode *left, *right; // ponteiros de ligação na árvore 
char *word;  //   string alojada dinamicamente, com a palavra associada 
VecLoc *vec;            
} TNode;

typedef struct {     
// Contexto para registar ocorrência de uma palavra 
TNode **rootPtr;  //   endereço do ponteiro raiz da árvore binária 
Location locData; //   localização da linha, para registar nas ocorrências 
} ContextTree; 

void tAddWord( TNode **rootPtr, char *data, Location *loc ); 
void tBalance(TNode **rootPtr); 
VecLoc *tFindWord( TNode *root, char *data ); 
void tDelete( TNode *root ); 
int wordStoreTree( char *word, void *context ); 

TNode *treeToSortedList( TNode *r, TNode *link );
TNode* sortedListToBalancedTree(TNode **listRoot, int n);





#endif
