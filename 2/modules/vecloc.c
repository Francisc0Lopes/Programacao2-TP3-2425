#include "vecloc.h"
#include <stdlib.h>
#include <string.h>

#define VECLOC_BLOCK 8

VecLoc *vlCreate( void ){
  VecLoc *vec = (VecLoc *)malloc(sizeof(VecLoc));
    if (!vec) return NULL;
    vec->space = VECLOC_BLOCK;
    vec->count = 0;
    vec->data = (Location *)malloc(vec->space * sizeof(Location));
    if (!vec->data) {
        free(vec);
        return NULL;
    }
    return vec;
} 

int vlAdd( VecLoc *vec, Location *loc ){
 if (!vec || !loc) return 0;
    // Verifica se já existe (última posição)
    if(vec->count > 0){
        Location *last = &vec->data[vec->count - 1];
        if (last->fileIdx == loc->fileIdx &&
            last->line == loc->line &&
            last->offset == loc->offset) {
            return 0;
        }
    }
    // Redimensiona se necessário
    if(vec->count >= vec->space){
        int new_space = vec->space + VECLOC_BLOCK;
        Location *new_data = (Location *)realloc(vec->data, new_space * sizeof(Location));
        if (!new_data) return 0;
        vec->data = new_data;
        vec->space = new_space;
    }
    vec->data[vec->count] = *loc;
    vec->count++;
    return 1;
}

int vlSize( VecLoc *vec ){
    if(!vec) return 0;
    return vec->count;
}


Location *vlGet( VecLoc *vec, int idx ){
   if(!vec || idx < 0 || idx >= vec->count) return NULL;
    return &vec->data[idx];
}


void vlDelete( VecLoc *vec ){
    if(!vec) return;
    free(vec->data);
    free(vec);
}