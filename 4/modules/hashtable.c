#include "hashtable.h"
#include <string.h>
#include <stdlib.h>



HTable *hCreate( int size ){
  	HTable *htable= malloc(sizeof(HTable));
	if(htable==NULL){
	   return NULL;
	}

	htable->size=size;
	htable->table=malloc(htable->size*sizeof(HLNode*));

   	if(htable->table==NULL){
		return NULL;
	}

	return htable;
}


//funçao hash(djb2) para idexaçao na hash-table
unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
    return hash;
}


void hAddWord( HTable *ht, char *data, Location *loc ){
	unsigned long index = hash((unsigned char*)data) % TABLE_SIZE;
	 HLNode *current = ht->table[index];
	
     while(current!=NULL){
		 if(strcoll(current->word,data)==0){
			 vlAdd(current->vec,loc);
			 return;
			}
		current=current->next;
	}
	
	HLNode *n =malloc(sizeof(HLNode));
		
	if(n!=NULL){
		n->vec=vlCreate();
		n->word=strdup(data);
		vlAdd(n->vec,loc);
		n->next=ht->table[index];
		ht->table[index]=n;
	}

}


VecLoc *hFindWord( HTable *ht, char *data ){
	if(ht==NULL){
		return NULL;
	}
	for(int i =0;i<ht->size;i++){
		HLNode *current = ht->table[i];

        while(current!=NULL){
	    	if(strcoll(data,current->word)==0){
		  		return current->vec;
	  		}
			else{
		  		current=current->next;
			}
		}
	}
	return NULL;
}
 



void hDelete( HTable *ht ){
	if(ht!=NULL){
		for(int i =0;i<ht->size;i++){
			HLNode *current = ht->table[i];
			while(current!=NULL){
	 			HLNode *next= current->next;
	 			vlDelete(current->vec);
	 			free(current->word);
	 			free(current);
	 			current=next;
			}
		}

		free(ht->table);
		free(ht);
	}
}



int wordStoreHash( char *word, void *context ){
	ContextHash *pointer = (ContextHash*)context;
	hAddWord(pointer->tab,word,&(pointer->locData));
    return 1;
} 