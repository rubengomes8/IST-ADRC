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

	//printf("prefix: %s\n", prefix);
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


	if(fp){
		fgets(prefix, sizeof(prefix), fp);
		root = newNode(-1);
		while(fscanf(fp, "%s\t%d", prefix, &nextHop) != EOF){

			if(!strcmp(prefix, "e")){ //epsilon do enunciado
				root->nextHop = nextHop;
			}else{

				root = InsertPrefix(root, prefix, nextHop);

			}
			

		}
	}

	return root;
}

int getLevelCount(binaryTree *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftMaxLevel = 1 + getLevelCount(root->left);
    int rightMaxLevel = 1 + getLevelCount(root->right);
    if (leftMaxLevel > rightMaxLevel)
    {
        return leftMaxLevel;
    }
    else
    {
        return rightMaxLevel;
    }
}

void printLevel(binaryTree *node, int level, int flag, char *prefix)
{
    if (node != NULL && level == 0)
    {	
		if(node->nextHop!=-1)
		{
			if (strlen(prefix)==0)
				printf("  e\t\t");
			else
			{
				//printf("%d |\t", flag);
				printf(" %s\t\t", prefix);
			}
			
        	printf("%d\n ", node->nextHop);
			
		}
    }   
    else if (node != NULL)
    {
		//if (flag!=-1)	
		//	printf("%d", flag);
		char aux[level];
		strcpy(aux, prefix);
        printLevel(node->left, level - 1, 0, strcat(aux, "0"));	
		strcpy(aux, prefix);	
        printLevel(node->right, level - 1, 1, strcat(aux, "1"));
		//printf("prefixo: %s\n", prefix);
		prefix[0]='\0';
		aux[0]='\0';
		//printf("prefixo: %s\n", prefix);
    }
}

//PrintTable, that receives as input a prefix tree and prints to screen the corresponding prefix table;
void PrintTable(binaryTree *root){
	
	int i;
    int levelCount = getLevelCount(root);


	char prefix[levelCount];
	prefix[0]='\0';
	
	//printf("%ld\n",strlen(prefix) );

	printf("Tabela:\n");
	printf("Prefixo | Nexthop \n");
    for (i = 0; i < levelCount; i++)
    {
		
        printLevel(root, i,-1, prefix);
		prefix[0]='\0';
		
		
    }

}

//LookUp, that receives as input a prefix tree and an address and returns the next-hop for that address;
//011101100
int LookUp(binaryTree *root, char *address){

	//Vai andando para baixo na árvore até chegar a uma folha da árvore
	int lastHop;
	int i;
	int j = 1;
	binaryTree *aux = root;
	char addr[18];
	strcpy(addr, address);
	addr[16] = '\0';

	lastHop = aux->nextHop;
	for(i = 0; i<16; i++){

		if(aux->left == NULL && aux->right == NULL)
			break;
		else{
			if(addr[0] == '0'){

				if(aux->left != NULL)
					aux = aux->left;
				else
					break;
				if(aux->nextHop != -1){
					lastHop = aux->nextHop;
					/*if(aux->left == NULL && aux->right == NULL)
						break;*/
				}

			}else if (addr[0] == '1'){

				if(aux->right != NULL)
					aux = aux->right;
				else 
					break;
				if(aux->nextHop != -1){
					lastHop = aux->nextHop;
					/*if(aux->left == NULL && aux->right == NULL)
						break;*/
				}

			}else{

				//Significa que o ficheiro de texto está incorreto?
				printf("Endereço inválido, com caracteres diferentes de 0 e de 1\n");
				exit(-1);
			}
		}
		//retirar o caracter que já foi tratado (o 1º)
		while(addr[j] != '\0'){
			addr[j-1] =  addr[j];
			j++;
		}
		addr[j-1] = '\0';
		j=1;

	}
//1011101100110011
//011101100110011
//11101100110011
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
			if(aux->left != NULL)
			{
				aux = aux->left;
				flag = 'l';
			} else {
				printf("Esse prefixo não existe... A terminar tarefa...\n");
				return root;
			}
			

		}else if (prefix[0] == '1'){

			prev = aux;
			if (aux->right != NULL){
				aux = aux->right;
				flag = 'r';
			} else {
				printf("Esse prefixo não existe... A terminar tarefa...\n");
				return root;
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

	compressTreeRecursive(NULL, root, root->nextHop, 's');

	return root;
}

void compressTreeRecursive(binaryTree *prev, binaryTree *root, int nextHop, char direction){
	//se não for root compara com next Hop q veio de cima
		//se for igual 
			//se nao tiver filhos apaga-se e retorna o seu Hop
			//se tiver pelo menos 1 filho mete seu Hop a -1 e envia left e right seu Hop
		//se for diferente
			//envia left e right seu hop
	//se for root envia left e right seu hop

	binaryTree *aux;
	if(prev == NULL){ //1ª invocação -> é root
		aux = root;
		if(aux->left != NULL){
			compressTreeRecursive(aux, root, aux->nextHop, 'l');
		}
		if(aux->right != NULL){
			compressTreeRecursive(aux, root, aux->nextHop, 'r');
		}

	}else{

		if(direction == 'l')
			aux = prev->left;
		else
			aux = prev->right;
		//Envia para a esquerda e direita com o Hop que vinha de cima
		if(aux->nextHop == -1){
			if(aux->left != NULL){
				//l_exist = true;
				compressTreeRecursive(aux, root, nextHop, 'l');
			}
			if(aux->right != NULL){
				//r_exist = true;
				compressTreeRecursive(aux, root, nextHop, 'r');
			}

			//se já não tem filhos apaga-se
			if(aux->left == NULL && aux->right == NULL){

				free(aux);
				if(direction == 'l'){
					prev->left = NULL;
				}
				else{
					prev->right = NULL;
				}
			}

		}else{
			//por implementar
			if(aux->nextHop==nextHop){
				if(aux->left==NULL && aux->right==NULL){
					free(aux);
					if(direction == 'l'){
						prev->left = NULL;
					}
					else{
						prev->right = NULL;
					}
				}
				else
				{
					aux->nextHop = -1;
					if(aux->left != NULL){
						//l_exist = true;
						compressTreeRecursive(aux, root, nextHop, 'l');
					}
					if(aux->right != NULL){
						//r_exist = true;
						compressTreeRecursive(aux, root, nextHop, 'r');
					}

				}
				
			}
			else{
				//diferente de cima
				if(aux->left != NULL){
					//l_exist = true;
					compressTreeRecursive(aux, root, aux->nextHop, 'l');
				}
				if(aux->right != NULL){
					//r_exist = true;
					compressTreeRecursive(aux, root, aux->nextHop, 'r');
				}

			} 

		}


	}

}

//Faz free dos nós recursivamente
void freeTree(binaryTree *prev, binaryTree *root, char direction){

	binaryTree *cur;

	if(prev == NULL){ //root
		cur = root;
	} 
	else{
		if(direction == 'l')
			cur = prev->left;
		else
			cur = prev->right;
	}
	

	if(cur->left != NULL)
		freeTree(cur, root, 'l');
	if(cur->right != NULL)
		freeTree(cur, root, 'r');

	free(cur);
}


