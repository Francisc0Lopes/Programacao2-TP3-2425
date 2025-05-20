#ifndef VECLOC_H
#define VECLOC_H

typedef struct{ // Descritor de uma localização de linha
 int fileIdx; // índice no array de ponteiros para os nomes dos ficheiros
 int line; // número da linha no texto
 long offset; // posição do início da linha no ficheiro
} Location;
typedef struct{ // Descritor de um vetor de localizações de linhas
 int space; // quantidade de elementos alojados no array dinâmico
 int count; // quantidade de elementos ocupados no array dinâmico
 Location *data; // aponta array alojado dinamicamente
} VecLoc; 




VecLoc *vlCreate( void ); 
int vlAdd( VecLoc *vec, Location *loc ); 
int vlSize( VecLoc *vec ); 
Location *vlGet( VecLoc *vec, int idx ); 
void vlDelete( VecLoc *vec ); 



#endif // VECLOC_H
