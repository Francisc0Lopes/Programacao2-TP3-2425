#include "hashtable.h"
#include <string.h>
#include <stdlib.h>

HTable *hCreate( int size ){
    if (size <= 0) return NULL;
    HTable *ht = (HTable *)malloc(sizeof(HTable));
    if (!ht) return NULL;
    ht->size = size;
    ht->table = (HLNode **)calloc(size, sizeof(HLNode *));
    if (!ht->table) {
        free(ht);
        return NULL;
    }
    return ht;
}

void hAddWord( HTable *ht, char *data, Location *loc ){
  if (!ht || !data || !loc) return;
    int idx = wordStoreHash(data, ht) % ht->size;
    if (idx < 0) idx += ht->size;

    HLNode *node = ht->table[idx];
    while (node) {
        if (strcmp(node->word, data) == 0) {
            vlAdd(node->vec, loc);
            return;
        }
        node = node->next;
    }

    // Palavra não existe, criar novo nó
    HLNode *newNode = (HLNode *)malloc(sizeof(HLNode));
    if (!newNode) return;
    newNode->word = strdup(data);
    if (!newNode->word) {
        free(newNode);
        return;
    }
    newNode->vec = vlCreate();
    if (!newNode->vec) {
        free(newNode->word);
        free(newNode);
        return;
    }
    vlAdd(newNode->vec, loc);
    newNode->next = ht->table[idx];
    ht->table[idx] = newNode;
}


VecLoc *hFindWord( HTable *ht, char *data ){
 if (!ht || !data) return NULL;
    int idx = wordStoreHash(data, ht) % ht->size;
    if (idx < 0) idx += ht->size;

    HLNode *node = ht->table[idx];
    while (node) {
        if (strcmp(node->word, data) == 0) {
            return node->vec;
        }
        node = node->next;
    }
    return NULL;
}



void hDelete( HTable *ht ){
    if (!ht) return;
    for (int i = 0; i < ht->size; i++) {
        HLNode *node = ht->table[i];
        while (node) {
            HLNode *next = node->next;
            free(node->word);
            if (node->vec) vlDelete(node->vec);
            free(node);
            node = next;
        }
    }
    free(ht->table);
    free(ht);
}



int wordStoreHash( char *word, void *context ){
  if (!word || !context) return 1;
    ContextHash *ctx = (ContextHash *)context;
    hAddWord(ctx->tab, word, &ctx->locData);
    return 1;
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