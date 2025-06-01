#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include "tree.h"
#include "allFuncs.h"




void tAddWord( TNode **rootPtr, char *data, Location *loc ){
	
	if(*rootPtr==NULL){
		TNode *n =malloc(sizeof(*n));

		if(n!=NULL){
		n->vec=vlCreate();
		n->word=strdup(data);
		vlAdd(n->vec,loc);
		n->left=n->right=NULL;
		*rootPtr=n;
		}

		return;
	}

	int cmp = strcoll(data,(*rootPtr)->word);

	if(cmp==0){
        vlAdd((*rootPtr)->vec,loc);
	}
	else if(cmp<0){
		tAddWord(&(*rootPtr)->left,data,loc);
	}
	else{
		tAddWord(&(*rootPtr)->right,data,loc);
	}
	
}


//TNode *treeToSortedList( TNode *r, TNode *link );
//TNode* sortedListToBalancedTree(TNode **listRoot, int n);


void tBalance(TNode **rootPtr) {
    TNode *sortedList = treeToSortedList(*rootPtr, NULL);
    int count = 0;  // numero de elemnos na lista
    TNode *tmp = sortedList;
    while (tmp != NULL){
        count++;
        tmp = tmp->right;
    }
    *rootPtr = sortedListToBalancedTree(&sortedList, count);
}


VecLoc *tFindWord( TNode *root, char *data ){
	
	if(root==NULL){
		return NULL;
	}
	int cmp= strcoll(data,root->word);
	
	if(cmp==0){
		return root->vec;
	}
	if(cmp>0){
		return tFindWord(root->right,data);
	}
	else{
		return tFindWord(root->left,data);
	}
	
	return NULL;
}
 
void tDelete( TNode *root ){
 	if(root!=NULL){
		tDelete(root->left);
		tDelete(root->right);
		vlDelete(root->vec);
		free(root->word);
    	free(root);
	}
}


int wordStoreTree( char *word, void *context ){
	ContextTree *cntx = (ContextTree*)context;
	tAddWord(cntx->rootPtr,word,&cntx->locData);
	return 1;
}




//Funçoes de ajuda para balanceamento da arvore

TNode *treeToSortedList( TNode *r, TNode *link ){ 
	TNode * p; 
	if( r == NULL ) return link; 
	p = treeToSortedList( r->left, r ); 
	r->left = NULL; 
	r->right = treeToSortedList( r->right, link ); 
	return p; 
} 

TNode* sortedListToBalancedTree(TNode **listRoot, int n) { 
	if( n == 0 ) return NULL; 
	TNode *leftChild = sortedListToBalancedTree(listRoot, n/2); 
	TNode *parent = *listRoot; 
	parent->left = leftChild; 
	*listRoot = (*listRoot)->right; 
	parent->right = sortedListToBalancedTree(listRoot, n-(n/2 + 1) ); 
	return parent; 
}
