#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct _binaryTree binaryTree;
typedef struct _hopList hopList;


binaryTree *newNode(int nextHop);
void removeNode(binaryTree *nodeToBeRemoved);
binaryTree *insertNewNode(char *prefix, binaryTree *root);

binaryTree *PrefixTree(FILE *fp);

int getLevelCount(binaryTree *root);
void printLevel(binaryTree *node, int level,int flag, char *prefix);
void PrintTable(binaryTree *root);
void compressTreeRecursive(binaryTree *prev, binaryTree *root, int nextHop, char direction);
void freeTree(binaryTree *prev, binaryTree *root, char direction);
void freeTreeHops(binaryTree *prev, binaryTree *root, char direction);

binaryTree * compressTreeOptimal(binaryTree *root);
hopList * Step1_and_2(binaryTree* root, int hop);
void Step3(binaryTree *prev, binaryTree *root, int hop, char direction);
bool checkHopInMyList(hopList *hops, int hop);
void freeHopList(binaryTree *node);
void freeIntersectedList(hopList *node);
hopList* new_hop(int hop);
hopList* percolate(hopList *left, hopList *right);

int LookUp(binaryTree *root, char *address);
binaryTree *InsertPrefix(binaryTree *root, char *prefix, int nextHop);
binaryTree *DeletePrefix(binaryTree *root, char *prefix);
binaryTree *CompressTree(binaryTree *root);
