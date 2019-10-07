#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

typedef struct _binaryTree binaryTree;


binaryTree *newNode(int nextHop);
void removeNode(binaryTree *nodeToBeRemoved);
binaryTree *insertNewNode(char *prefix, binaryTree *root);

binaryTree *PrefixTree(FILE *fp);

int getLevelCount(binaryTree *root);
void printLevel(binaryTree *node, int level,int flag, char *prefix);
void PrintTable(binaryTree *root);
void compressTreeRecursive(binaryTree *prev, binaryTree *root, int nextHop, char direction);
void freeTree(binaryTree *prev, binaryTree *root, char direction);
void compressTreeOptimal(binaryTree *root);


int LookUp(binaryTree *root, char *address);
binaryTree *InsertPrefix(binaryTree *root, char *prefix, int nextHop);
binaryTree *DeletePrefix(binaryTree *root, char *prefix);
binaryTree *CompressTree(binaryTree *root);
