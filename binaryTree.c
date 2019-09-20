#include "binaryTree.h"

struct _binaryTree{
	int nextHop;
	struct _binaryTree *left;
	struct _binaryTree *right;
};


struct _binaryTree *newNode(int nextHop){

	struct _binaryTree *node = (struct _binaryTree*) malloc(sizeof(struct _binaryTree));

	node->nextHop = nextHop;

	node->left = NULL;
	node->right = NULL;
	return node;
}