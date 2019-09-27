#include "lmp.h"
#include "binaryTree.h"

int main(int argc, char *argv[]){
	int exit=0;
	binaryTree *root;
	char option[2];
	char address[18];
	char aux[25];
	int nextHop;
	FILE *fp = fopen("./prefixTable.txt", "r");
	
	root = PrefixTree(fp); //Cria árvore binária através do ficheiro de texto
	
	do{
		printf("\nOPCOES:\n");
		printf("- Imprimir tabela                  --> premir p\n- Procurar next hop de um endereço --> premir l\n- Inserir uma entrada na tabela    --> premir i\n- Apagar uma entrada da tabela     --> premir d\n- Comprimir a tabela               --> premir c\n- Sair                             --> premir e\n\n");


		//fflush(stdin);

		fgets(option, 2, stdin);

        //Limpa o buffer
        while ((getchar()) != '\n'){
    
        }
        
        option[1]='\0';
		//printf("%s\n", option);
		if(!strcasecmp(option, "p")){
			PrintTable(root);
		}
		else if(!strcasecmp(option, "l")){

			printf("- Digite o endereço de 16 bits sem espaços\n");
			fgets(address, 17, stdin);
            address[16] = '\0';
            //printf("address: %s\n", address);
			nextHop = LookUp(root, address);
            printf("\nO próximo hop do endereço especificado é %d\n", nextHop);
			strcpy(address, "\0");

		}else if(!strcasecmp(option, "i")){

			printf("- Digite o prefixo e o next hop associado com o formato <prefixo nextHop>\n");
			fgets(aux, 25, stdin);
			sscanf(aux, "%s %d", address, &nextHop);
			InsertPrefix(root, address, nextHop);
			strcpy(address, "\0");
			
			
		}else if(!strcasecmp(option, "d")){

			printf("- Digite o prefixo que pretende eliminar\n");
			fgets(address, 18, stdin);
            address[strlen(address)-1] = '\0';
			DeletePrefix(root, address);
			strcpy(address, "\0");
			
		}else if(!strcasecmp(option, "c")){

			printf("A implementar...\n");
			CompressTree(root);
			
		}else if(!strcasecmp(option, "e")){
			//dar free's
			exit=1;
		}else{

			printf("Comando inválido\n");
		}
		
	}while(exit==0);
	fclose(fp);
}
