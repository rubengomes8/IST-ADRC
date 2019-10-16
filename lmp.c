#include "lmp.h"
#include "binaryTree.h"


int main(int argc, char *argv[]){
	int exit=0;
	FILE *fp ;
	binaryTree *root;
	char option[2];
	char address[18];
	char aux[100];
	int nextHop;
	if(argc<2){
		printf("Falta de argumentos\nExemplo: ./lmp tabela_prefixos.txt");
		return -1;
	}
	else if(argc > 2){
		printf("Excesso de argumentos\nExemplo: ./lmp tabela_prefixos.txt");
		return -1;
	}
	else{
		fp=fopen(argv[1], "r");
	}
	
	root = PrefixTree(fp); //Cria árvore binária através do ficheiro de texto
	
	do{
		printf("\nOPCOES:\n");
		printf("- Imprimir tabela                  --> premir p\n- Procurar next hop de um endereço --> premir l\n- Inserir uma entrada na tabela    --> premir i\n- Apagar uma entrada da tabela     --> premir d\n- Comprimir a tabela               --> premir c\n- Compressão ótima                 --> premir o\n- Sair                             --> premir e\n\n");


		//fflush(stdin);

		fgets(option, 2, stdin);

        //Limpa o buffer
        while ((getchar()) != '\n'){
    
        }
        free(NULL);
        option[1]='\0';
		//printf("%s\n", option);
		if(!strcasecmp(option, "p")){
			PrintTable(root);
		}
		else if(!strcasecmp(option, "l")){

			printf("- Digite o endereço de 16 bits sem espaços\n");
			fgets(aux, 100, stdin);
			if(strlen(aux) == 17){

				 aux[16] = '\0';
				if(checkInput(aux) == -1){
					printf("Endereço tem de conter apenas 0's e 1's\n");
					continue;
				}
	            //printf("address: %s\n", address);
				nextHop = LookUp(root, aux);
				if(nextHop>0){
	            	printf("\nO próximo hop do endereço especificado é %d\n", nextHop);
				}
				else
				{
					printf("Endereço sem correspondencia na tabela, pacote descartado\n");
				}
				
				strcpy(aux, "\0");

			}else{
				printf("Endereço com tamanho inválido.\n");
			}
           
		}else if(!strcasecmp(option, "i")){

			printf("- Digite o prefixo e o next hop associado com o formato <prefixo nextHop>\n");
			fgets(aux, 100, stdin);
			sscanf(aux, "%s %d", address, &nextHop);
			if(strlen(address)>16){
				printf("Limite do prefixo ultrapassado\n");
				continue;
				
			}
			if(!strcmp(address, "e")){
				if(nextHop <= 0){
					printf("Hop tem de ser positivo\n");
					continue;
				}
				changeRootHop(root, nextHop);
				strcpy(address, "\0");
				continue;
			}
			if(checkInput(address) == -1){
				printf("Prefixo tem de conter apenas 0's e 1's\n");
				continue;
			}
			if(nextHop <= 0){
				printf("Hop tem de ser positivo\n");
				continue;
			}
			InsertPrefix(root, address, nextHop);
			strcpy(address, "\0");
			
			
		}else if(!strcasecmp(option, "d")){

			printf("- Digite o prefixo que pretende eliminar\n");
			fgets(address, 100, stdin);
			/*if(!strcmp(address, "e\n")){
				changeRootHop(root, -1);
				strcpy(address, "\0");
				continue;
			}*/

            address[strlen(address)-1] = '\0';
			if(checkInput(address) == -1){
				printf("Prefixo tem de conter apenas 0's e 1's\n");
				continue;
			}
			DeletePrefix(root, address);
			strcpy(address, "\0");
		
		}else if(!strcasecmp(option, "o")){
			//if(!checkRootHop(root, -1))
			root=compressTreeOptimal(root);
			//else
			//	printf("\nImpossível realizar compressão ótima, pois não está associado um next-hop default.\n");

		}
		else if(!strcasecmp(option, "c")){
			
			CompressTree(root);
			
		}else if(!strcasecmp(option, "e")){
			//dar free's
			freeTree(NULL, root, 's');
			printf("\nPrograma terminado.\n");
			exit=1;
		}else{

			printf("Comando inválido\n");
		}
		
	}while(exit==0);
	fclose(fp);
}

int checkInput(char msg[]){
	int i = 0;
	
	do{
		if(msg[i] != '0' &&  msg[i] != '1')
			return -1; //fail
		i++;
	}while(msg[i] != '\0');
	return 0; //success
}