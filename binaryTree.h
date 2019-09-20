#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

typedef struct _binaryTree binaryTree;


binaryTree *newNode(int nextHop);
void removeNode(binaryTree *nodeToBeRemoved);


binaryTree *PrefixTree(FILE *fp);
void PrintTable(binaryTree *root);
int LookUp(binaryTree *root, char *address);
binaryTree *InsertPrefix(binaryTree *root, char *prefix, int nextHop);
binaryTree *DeletePrefix(binaryTree *root, char *prefix);
binaryTree *CompressTree(binaryTree *root);