#include "lmp.h"
#include "binaryTree.h"

int main(int argc, char *argv[]){
	int exit=0;
	binaryTree *root;
	char option[2];
	FILE *fp = fopen("./prefixTable.txt", "r");
	
	root = PrefixTree(fp); //Cria árvore binária através do ficheiro de texto
	
	do{
		printf("Options:\n");
		printf("-Print Table press p\n");
		printf("-Exit press e\n");
		fgets(option, 2, stdin);
		if(strcmp(option, "p")==0)
			PrintTable(root);
		else if(strcmp(option, "e")==0)
		{
			exit=1;
		}
		
	}while(exit==0);
	fclose(fp);
}