#include "lmp.h"
#include "binaryTree.h"

int main(int argc, char *argv[]){

	binaryTree *root;

	FILE *fp = fopen("./prefixTable.txt", "r");

	root = PrefixTree(fp); //Cria árvore binária através do ficheiro de texto

	fclose(fp);
}