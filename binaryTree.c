#include "binaryTree.h"

//If left = right = null --> the node is a leaf

struct _binaryTree{
	int nextHop;
	struct _binaryTree *left;
	struct _binaryTree *right;
	struct _hopList *head_hops;
};

struct _hopList{
	int hop;
	struct _hopList *next;
};


binaryTree *newNode(int nextHop){

	struct _binaryTree *node = (struct _binaryTree*) malloc(sizeof(struct _binaryTree));

	node->nextHop = nextHop;
	node->head_hops = NULL;
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
			printf("Prefixos invalidos com caracteres diferentes de 0 e de 1\n");
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
				printf("           e ");
			else
			{
				//printf("%d |\t", flag);
				printf(" %10s ", prefix);
			}
			
        	printf("|%d\n ", node->nextHop);
			
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
	if(levelCount==0){
		printf("Tabela vazia\n");
	}
	//printf("\tTabela:\n");
	printf("      Prefixo|Nexthop \n");
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
/*
//DeletePrefix, that receives as input a prefix tree and a prefix and returns a prefix tree with the prefix withdrawn;
binaryTree *DeletePrefix(binaryTree *root, char *prefix){
	//se for folha faz free do node e mete o pai a apontar para NULL, se não for apenas mete o nextHop a -1
	//ter em atenção que o prefixo pode não existir
	binaryTree *aux = root;
	binaryTree *cur;
	binaryTree *prev;
	int i = 1;
	char flag;
	binaryTree *lastWithHop = root;
	char *lastPrefix = (char *)malloc(strlen(prefix)*sizeof(char)+1);
	


	while(strlen(prefix) > 0)
	{
		if(prefix[0] == '0'){

			prev = aux;
			if(prev->nextHop != -1){
				lastWithHop = prev;
				strcpy(lastPrefix, prefix);
			}
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
			if(prev->nextHop != -1){
				lastWithHop = prev;
				strcpy(lastPrefix, prefix);
			}
			if (aux->right != NULL){
				aux = aux->right;
				flag = 'r';
			} else {
				printf("Esse prefixo não existe... A terminar tarefa...\n");
				return root;
			}

			

		}else{

			//Significa que o ficheiro de texto está incorreto?
			printf("Prefixos invalidos com caracteres diferentes de 0 e de 1\n");
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
		i=1;
		if(prev->nextHop == -1){
			aux = lastWithHop;
			while(strlen(lastPrefix) > 0){
				if(lastPrefix[0] == '0'){
					aux = aux->left;
				}else if(lastPrefix[0] == '1'){
					aux = aux->right;
				}

				while(lastPrefix[i] != '\0'){
					lastPrefix[i-1] =  lastPrefix[i];
					i++;
				}
				lastPrefix[i-1] = '\0';
				i=1;

				if(lastPrefix[0] == '0'){
					cur = aux->left;
					free(aux);
				}else if(lastPrefix[0] == '1'){
					cur = aux->right;
					free(aux);
				}
				aux=cur;
			}
		}else{
			aux->nextHop = -1;
		}
		
	}
	free(lastPrefix);
	return root;
}
*/

binaryTree *DeletePrefix(binaryTree *root, char *prefix){
	char px[strlen(prefix)];
	printf("prefixo de entrada %s, tamanho %d\n" , prefix, strlen(prefix));
	binaryTree * ret;
	int l=0,r=0;
	if(strlen(prefix) > 0 ){
		if(prefix[0]=='0'){
			if(root->left!=NULL){
				strcpy(px,prefix+1);
				printf(" prefixo: %s\n",prefix);
				printf(" %s\n",px);
				ret=DeletePrefix(root->left,px);
				l=1;
			}
			else
			{
				printf("prefixo não encontrado\n");
				return(root);
			}
			
		}
		else if(prefix[0]=='1'){
			if(root->right!=NULL){
				strcpy(px,prefix+1);
				printf(" prefixo: %s\n",prefix);
				printf(" %s\n",px);
				ret=DeletePrefix(root->right,px);
				r=1;
			}
			else
			{
				printf("prefixo não encontrado\n");
				return(root);
			}
		}
	}

	if(strlen(prefix)==0){
		if(root->left==NULL && root->right==NULL){
			printf("apaguei prefixo: %d", root->nextHop);
			free(root);	
			root = NULL; //?????
			return NULL;
		}
		else{
			root->nextHop=-1;
			return root;
		}
	}

	if(ret==NULL && root->nextHop==-1){
		if(l==1){
			if(root->right == NULL)
			{
				//free(root->left);
				root->left=NULL;
				free(root);
				root=NULL; //????
				return NULL;
			}else{
				root->left = NULL;
				return root;
			}

		}
		if(r==1){
			if(root->left == NULL){
				//free(root->right);
				root->right=NULL;
				free(root);
				root=NULL;//????
				return NULL;
			}else{
				root->right = NULL;
				return root;
			}
			
		}
	}
	else if(ret==NULL){
		if(l==1){
			//free(root->left); ???
			root->left=NULL;
			return root;
		}
		if(r==1){
			//free(root->right);
			root->right=NULL;
			return root;
		}

	}
	
}
	


	

//CompressTree, that receives as input the prefix tree of a prefix table and returns another prefix tree representing a prefix table with a smaller number of entries.
binaryTree *CompressTree(binaryTree *root){

	compressTreeRecursive(NULL, root, root->nextHop, 's');
	//clusterTree(root);
	
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

		/************************************************* Fui eu q adicionei para esquecer o clusterTree ***************************************************/

		if(aux->left != NULL && aux->right != NULL && aux->left->nextHop == aux->right->nextHop && aux->left->nextHop != -1){
			if(aux->left->left == NULL && aux->left->right == NULL && aux->right->left == NULL && aux->right->right == NULL){ //apaga folhas parentes com mesmo hop
				aux->nextHop = aux->left->nextHop;
				free(aux->left);
				free(aux->right);
				aux->left = NULL;
				aux->right = NULL;
			}else{
				aux->nextHop=aux->left->nextHop;
				aux->left->nextHop = -1;
				aux->right->nextHop = -1;
			}
		}
		/***************************************************************************************************************************************************/

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


		/************************************************* Fui eu q adicionei para esquecer o clusterTree ***************************************************/
		if(aux->left != NULL && aux->right != NULL && aux->left->nextHop == aux->right->nextHop && aux->left->nextHop != -1){
			if(aux->left->left == NULL && aux->left->right == NULL && aux->right->left == NULL && aux->right->right == NULL){ //apaga folhas parentes com mesmo hop
				aux->nextHop = aux->left->nextHop;
				free(aux->left);
				free(aux->right);
				aux->left = NULL;
				aux->right = NULL;
			}else{
				aux->nextHop=aux->left->nextHop;
				aux->left->nextHop = -1;
				aux->right->nextHop = -1;
			}
		}
		/***************************************************************************************************************************************************/


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
/*
int clusterTree(binaryTree * node){
	int l, r;
	if(node->left != NULL){
		
		l=clusterTree(node->left);
	}
	if(node->right != NULL){
		
		r=clusterTree(node->right);
	}
	//se os nextHops dos filhos, l e r forem iguais 
	if(node->nextHop==l || node->nextHop==-1){
		if(r==l){
			printf("%d %d\n", r, l);
			printf("%d\n",  node->nextHop);			
			if(node->left->left==NULL && node->left->right==NULL){
				printf("adssfd\n");
				free(node->left);
				free(node->right);
				node->nextHop=r;		
			}
			else{
				node->nextHop=-1;
			}
		}
	}
	return node->nextHop;
}*/

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

//Faz free do hops list do nós
void freeTreeHops(binaryTree *prev, binaryTree *root, char direction){

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

	freeHopList(cur);
}

binaryTree * compressTreeOptimal(binaryTree *root){
	//passo 1: cada nó passa a ter 0 ou 2 filhos root to leaves
	//e passo 2: leaves to root y = a inters b if a inters b != 0 else y = a union b
	root->head_hops=Step1_and_2(root, -2);
	hopList *ax=root->head_hops;
	
	printf("root->head_hops\n");
	while (ax!=NULL)
	{
		printf("%d, ",ax->hop);
		ax=ax->next;
	}
	printf("\n");

	//passo 3: root to leaves
	printf("aquiwe\n");
	Step3(NULL, root, root->nextHop, 's');
	freeHopList(root);
	return root;
}

hopList * Step1_and_2(binaryTree* root, int hop){

	if(root->nextHop != -1)
		hop = root->nextHop;

	if(root->left != NULL && root->right == NULL){
		root->right = newNode(hop);
		root->left->head_hops=Step1_and_2(root->left, hop);
		root->right->head_hops=new_hop(hop);
		root->nextHop = 0;
	}else if(root->left==NULL && root->right != NULL){
		root->left = newNode(hop);
		root->right->head_hops=Step1_and_2(root->right, hop);
		root->left->head_hops=new_hop(hop);
		root->nextHop = 0;
	}else if(root->left != NULL && root->right != NULL){
		root->left->head_hops=Step1_and_2(root->left, hop);
		root->right->head_hops=Step1_and_2(root->right, hop);
		root->nextHop = 0;
	}else{
		//não tem filhos		
		return new_hop(root->nextHop);
	}

	return percolate(root->left->head_hops,root->right->head_hops);
	

}

void Step3(binaryTree *prev, binaryTree *root, int hop, char direction){

	bool hopInList = false;

	binaryTree *aux;

	if(prev == NULL){ //root
		aux = root;
		aux->nextHop = aux->head_hops->hop;		//choose one hop from the list (first)
		//apagar a lista de hops??
		if(aux->left != NULL)
			Step3(aux, root, aux->nextHop, 'l');
		if(aux->right != NULL)
			Step3(aux, root, aux->nextHop, 'r');


	}else{

		if(direction == 'l')
			aux = prev->left;
		else if(direction == 'r')
			aux = prev->right;

		hopInList = checkHopInMyList(aux->head_hops, hop);

		if(hopInList == false){ //choose 1 (primeiro)
			aux->nextHop = aux->head_hops->hop;
			if(aux->left != NULL)
				Step3(aux, root, aux->nextHop, 'l');
			if(aux->right != NULL)
				Step3(aux, root, aux->nextHop, 'r');


		}else{ //hopInList == true -> apaga-se
			if(aux->right == NULL && aux->left == NULL){ //elimina o nó pq é folha
				freeHopList(aux);
				free(aux); //pai tem de apontar para NULL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				aux=NULL;
				if(direction == 'l')
					prev->left = NULL;
				else if(direction == 'r')
					prev->right = NULL;
			}else{ //retira o hop
				aux->nextHop = -1;
				if(aux->left != NULL)
					Step3(aux, root, hop, 'l');
				if(aux->right != NULL)
					Step3(aux, root, hop, 'r');

			}
		}

	}

	
	/*******************************************Verificar se ainda tem filhos ******************************************************/
	if(prev != NULL && aux!=NULL){
		freeHopList(aux);
		if(aux->nextHop == -1 && aux->left == NULL && aux->right == NULL ){

			free(aux);
			if(direction == 'l'){
				prev->left = NULL;
			}
			else{
				prev->right = NULL;
			}
		}
	} 
	


}

bool checkHopInMyList(hopList *hops, int hop){
	bool found = false;
	hopList *aux = hops;
	while(aux != NULL){
		if(aux->hop == hop){
			found = true;
			break;
		}
		aux = aux->next;
	}

	return found;
}

void freeHopList(binaryTree *node){
	hopList *cur = node->head_hops;
	hopList *prev = NULL;
	while(cur != NULL){
		prev = cur;
		cur = cur->next;
		free(prev);
	}
}

void freeIntersectedList(hopList *node){
	hopList *cur = node;
	hopList *prev = NULL;
	while(cur != NULL){
		prev = cur;
		cur = cur->next;
		free(prev);
	}
}


hopList* new_hop(int hop){
	struct _hopList *node = (struct _hopList*) malloc(sizeof(struct _hopList));
	node->hop = hop;
	node->next=NULL;
	return node;
}


hopList* percolate(hopList *left, hopList *right){
	
	hopList *aux_left=left;
	hopList *aux_right=right;
	hopList *intersectList=NULL, *auxIntList=NULL;
	hopList *unionList=NULL, *auxUnList=NULL;
	hopList *new_node=NULL;
	bool intersected=false;

	hopList *ax=left;

	printf("Left\n");
	while (ax!=NULL)
	{
		printf("%d, ",ax->hop);
		ax=ax->next;
	}
	printf("\n");

	printf("Right\n");
	ax=right;
	while (ax!=NULL)
	{
		printf("%d, ",ax->hop);
		ax=ax->next;
	}
	printf("\n");

	while(aux_left!=NULL && aux_right!=NULL){

		if(intersected==false){

			if(aux_left->hop < aux_right->hop){
				new_node=new_hop(aux_left->hop);
				
				if(intersectList==NULL){
					intersectList=new_node;
					auxIntList=new_node;
				}
				else
				{
					auxIntList->next=new_node;
					auxIntList=new_node;
				}

				aux_left=aux_left->next;
			}
			else if(aux_left->hop > aux_right->hop){
				new_node=new_hop(aux_right->hop);
				
				if(intersectList==NULL){
					intersectList=new_node;
					auxIntList=new_node;
				}
				else
				{
					auxIntList->next=new_node;
					auxIntList=new_node;
				}
				aux_right=aux_right->next;
			}
			else if (aux_left->hop == aux_right->hop)
			{
				intersected=true;
				freeIntersectedList(intersectList);
				new_node=new_hop(aux_right->hop);
				if(unionList==NULL){
					unionList=new_node;
					auxUnList=new_node;
				}
				else
				{
					auxUnList->next=new_node;
					auxUnList=new_node;
				}
				aux_left=aux_left->next;
				aux_right=aux_right->next;

			}				
			
		}else if(intersected==true){

			if(aux_left->hop < aux_right->hop){
				aux_left=aux_left->next;
			}
			else if(aux_left->hop > aux_right->hop){
				aux_right=aux_right->next;
			}
			else if (aux_left->hop== aux_right->hop)
			{
				new_node=new_hop(aux_right->hop);
				if(unionList==NULL){
					unionList=new_node;
					auxUnList=new_node;
				}
				else
				{
					auxUnList->next=new_node;
					auxUnList=new_node;
				}
				aux_left=aux_left->next;
				aux_right=aux_right->next;
			}
			
		}
	}


	while (aux_left!=NULL)
	{
		new_node=new_hop(aux_left->hop);
		if(auxIntList!=NULL){
			auxIntList->next=new_node;
			auxIntList=new_node;
		}
		else{
			auxIntList=new_node;
		}
		aux_left=aux_left->next;
	}

	while (aux_right!=NULL)
	{
		new_node=new_hop(aux_right->hop);
		if(auxIntList!=NULL){
			auxIntList->next=new_node;
			auxIntList=new_node;
		}
		else{
			auxIntList=new_node;
		}
		aux_right=aux_right->next;
	}

	/*
	ax=intersectList;
	while (ax!=NULL)
	{
		printf("intersect %d, ",ax->hop);
		ax=ax->next;
	}
	printf("\n");

	ax=unionList;
	while (ax!=NULL)
	{
		printf("union %d, ",ax->hop);
		ax=ax->next;
	}
	*/
	

	if(unionList==NULL){
		return intersectList;
	}
	else
	{
		return unionList;
	}
	
} 
/*
hopList * Step2( binaryTree *root){
	hopList *list_head_left = NULL;
	hopList *list_head_right = NULL;
	hopList *list_head = NULL;
	//post order - left right root

	if(root->left->left != NULL){
		list_head_left = Step2(root->left);
	}
	else{//nível 2
		
		root->left->nextHop;
	}

	if(root->right->left != NULL){
		list_head_right = Step2(root->right);
	}



}
*/

