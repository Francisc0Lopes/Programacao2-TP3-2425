#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include "vecloc.h"



VecLoc *vlCreate( void ){
 	VecLoc *vecloc= malloc(sizeof(VecLoc));
 	if(vecloc==NULL){
        return NULL;
    }
	Location *data=  malloc(INIT_ELEMS * sizeof(Location));
  	if(data==NULL){
	  	free(vecloc);
        return NULL;
    }
	vecloc->count=0;
	vecloc->space=INIT_ELEMS; //valor para exemplo
	vecloc->data=data;
	return vecloc;
}


int vlAdd( VecLoc *vec, Location *loc ){
	if(vec==NULL || loc==NULL){
		return 0;
	}
	
	if(vec->count>0){
		if(vec->data[vec->count-1].fileIdx==loc->fileIdx && vec->data[vec->count-1].line==loc->line && vec->data[vec->count-1].offset==loc->offset){
			return 0;
		}
	}

	if(vec->count>=vec->space){
		vec->data=realloc(vec->data,sizeof(Location)* (vec->space+10));
    	if(vec->data==NULL){
	    	return 0;
		}
		vec->space+=10;  // atualiza a capacidade do array após o aumento atraves do realloc
	}
	
	
	vec->data[vec->count]=*loc;
	vec->count++;
	
	return 1;
}





int vlSize( VecLoc *vec ){
	if(vec==NULL){
		return 0;
	}
	return vec->count;
}



Location *vlGet( VecLoc *vec, int idx ){
	if(vec==NULL ||idx<0||idx>=vec->count){
		return NULL;
	}
  	return &vec->data[idx];
}




void vlDelete( VecLoc *vec ){
  	if(vec!=NULL){	
	free(vec->data);
	free(vec);
	}
}
