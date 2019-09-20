#include "binaryTree.h"

//If left = right = null --> the node is a leaf

struct _binaryTree{
	int nextHop;
	struct _binaryTree *left;
	struct _binaryTree *right;
};


binaryTree *newNode(int nextHop){

	struct _binaryTree *node = (struct _binaryTree*) malloc(sizeof(struct _binaryTree));

	node->nextHop = nextHop;

	node->left = NULL;
	node->right = NULL;
	return node;
}

//Remove o nó. Nesta função só entra como argumentos folhas da árvore que se prentende remover. Se não for folha não se remove
//No código que invoca esta função, o pai tem de meter ponteiro que apontava para este nó a NULL
void removeNode(binaryTree *nodeToBeRemoved){
	free(nodeToBeRemoved);
}



binaryTree *PrefixTree(FILE *fp){
	binaryTree *root = NULL;
	return root;
}

void PrintTable(binaryTree *root){

}


int LookUp(binaryTree *root, char *address){

	return 0;
}

binaryTree *InsertPrefix(binaryTree *root, char *prefix, int nextHop){

	return root;
}


binaryTree *DeletePrefix(binaryTree *root, char *prefix){

	return root;
}


binaryTree *CompressTree(binaryTree *root){

	return root;
}
/*
PrefixTree, that reads a prefix table from a text file and returns a prefix tree representation of that table;
• PrintTable, that receives as input a prefix tree and prints to screen the corresponding prefix table;
• LookUp, that receives as input a prefix tree and an address and returns the next-hop for that address;
• InsertPrefix, that receives as input a prefix tree, a prefix and the associated next-hop, and returns a prefix tree
with the prefix included;
• DeletePrefix, that receives as input a prefix tree and a prefix and returns a prefix tree with the prefix withdrawn;
• CompressTree, that receives as input the prefix tree of a prefix table and returns another prefix tree representing
a prefix table with a smaller number of entries.*/