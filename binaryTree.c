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

binaryTree *insertNewNode(char *prefix, binaryTree *root){

	//ter em atenção que pode exister um nó já com esse prefixo. O que acontece?

	binaryTree *aux = root;
	binaryTree *new;
	int i=1;

	printf("prefix: %s\n", prefix);
	while(strlen(prefix) > 0)
	{
		if(prefix[0] == '0'){

			if (aux->left == NULL){
				new = newNode(-1);
				aux->left = new;
				aux = new;
			}else{
				aux = aux->left;
			}


		}else if (prefix[0] == '1'){

			if (aux->right == NULL){
				new = newNode(-1);
				aux->right = new;
				aux = new;
			}else{
				aux = aux->right;
			}

		}else{

			//Significa que o ficheiro de texto está incorreto?
			printf("Ficheiro de texto contém prefixos invalidos, com caracteres diferentes de 0 e de 1\n");
			exit(-1);
		}

		//retirar o caracter que já foi tratado (o 1º)
		while(prefix[i] != '\0'){
			prefix[i-1] =  prefix[i];
			i++;
		}
		prefix[i-1] = '\0';
		i=1;
	}

	return aux;	
}


//PrefixTree, that reads a prefix table from a text file and returns a prefix tree representation of that table;
binaryTree *PrefixTree(FILE *fp){
	char prefix[16];
	int nextHop;
	binaryTree *root;
	binaryTree *new;

	if(fp){
		fgets(prefix, sizeof(prefix), fp);
		root = newNode(-1);
		while(fscanf(fp, "%s\t%d", prefix, &nextHop) != EOF){

			if(!strcmp(prefix, "e")){ //epsilon do enunciado
				root->nextHop = nextHop;
			}else{
				new = insertNewNode(prefix, root);
				new->nextHop = nextHop;

			}
			

		}
	}

	return root;
}

//PrintTable, that receives as input a prefix tree and prints to screen the corresponding prefix table;
void PrintTable(binaryTree *root){

}

//LookUp, that receives as input a prefix tree and an address and returns the next-hop for that address;
int LookUp(binaryTree *root, char *address){

	int lastHop;
	binaryTree *aux = root;

	return lastHop;
}

//InsertPrefix, that receives as input a prefix tree, a prefix and the associated next-hop, and returns a prefix tree with the prefix included;
binaryTree *InsertPrefix(binaryTree *root, char *prefix, int nextHop){

	binaryTree *new = insertNewNode(prefix, root);
	new->nextHop = nextHop;
	return root;
}

//DeletePrefix, that receives as input a prefix tree and a prefix and returns a prefix tree with the prefix withdrawn;
binaryTree *DeletePrefix(binaryTree *root, char *prefix){
	//se for folha faz free do node e mete o pai a apontar para NULL, se não for apenas mete o nextHop a -1
	//ter em atenção que o prefixo pode não existir
	binaryTree *aux = root;
	binaryTree *prev;
	int i = 1;
	char flag;


	while(strlen(prefix) > 0)
	{
		if(prefix[0] == '0'){

			prev = aux;
			aux = aux->left;
			flag = 'l';

		}else if (prefix[0] == '1'){

			prev = aux;
			aux = aux->right;
			flag = 'r';

		}else{

			//Significa que o ficheiro de texto está incorreto?
			printf("Ficheiro de texto contém prefixos invalidos, com caracteres diferentes de 0 e de 1\n");
			exit(-1);
		}

		//retirar o caracter que já foi tratado (o 1º)
		while(prefix[i] != '\0'){
			prefix[i-1] =  prefix[i];
			i++;
		}
		prefix[i-1] = '\0';
		i=1;
	}

	if(aux->left == NULL && aux->right == NULL){
		if(flag == 'l')
			prev->left = NULL;
		else if(flag == 'r')
			prev->right = NULL;
		free(aux);
	} else{
		aux->nextHop = -1;
	}
	return root;
}

//CompressTree, that receives as input the prefix tree of a prefix table and returns another prefix tree representing a prefix table with a smaller number of entries.
binaryTree *CompressTree(binaryTree *root){

	return root;
}
