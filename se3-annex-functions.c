
TNode *treeToSortedList( TNode *r, TNode *link ){
	TNode * p;
	if( r == NULL )
		return link;
	p = treeToSortedList( r->left, r );
	r->left = NULL;
	r->right = treeToSortedList( r->right, link );
	return p;
}

TNode* sortedListToBalancedTree(TNode **listRoot, int n) {
	if( n == 0 )
		return NULL;
	TNode *leftChild = sortedListToBalancedTree(listRoot, n/2);
	TNode *parent = *listRoot;
	parent->left = leftChild;
	*listRoot = (*listRoot)->right;
	parent->right = sortedListToBalancedTree(listRoot, n-(n/2 + 1) );
	return parent;
}
