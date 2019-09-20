#include "binaryTree.h"

struct _binaryTree{
	int nextHop;
	struct _binaryTree *left;
	struct _binaryTree *right;
}