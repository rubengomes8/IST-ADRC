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
		printf("OPCOES:\n");
		printf("- Imprimir tabela                  --> premir p\n");
		printf("- Procurar next hop de um endereço --> premir l\n");
		printf("- Inserir uma entrada na tabela    --> premir i\n");
		printf("- Apagar uma entrada da tabela     --> premir d\n");
		printf("- Comprimir a tabela               --> premir c\n");
		printf("- Sair                             --> premir e\n");

		fflush(stdin);
		fgets(option, 3, stdin);
        option[1]='\0';
		printf("%s\n", option);printf("ola\n");

		if(!strcasecmp(option, "p")){
			PrintTable(root);
		}
		else if(!strcasecmp(option, "l")){

			printf("- Digite o endereço com o formato <abcdefgh.ijklmnop>\n");
			fgets(address, 18, stdin);
			LookUp(root, address);
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
			DeletePrefix(root, address);
			strcpy(address, "\0");
			
		}else if(!strcasecmp(option, "c")){

			printf("Por implementar...\n");
			
		}else if(!strcasecmp(option, "e")){
			//dar free's
			exit=1;
		}else{

			printf("Comando inválido\n");
		}
		
	}while(exit==0);
	fclose(fp);
}


/*
int read_terminal(int fd_rs, struct addrinfo *res_rs, char *streamID, int is_root, char *ipaddr, char* uport, char* tport,
        int tcp_sessions, int tcp_occupied, queue *redirect_queue_head, char *pop_addr, char *pop_tport, int is_flowing)
{
    char buffer[BUFFER_SIZE];
    int counter = 0; //conta tentativas de chamada de uma função

    fgets(buffer, BUFFER_SIZE, stdin);

    if(!strcasecmp(buffer, "streams\n"))
    {
        while(dump(fd_rs, res_rs) == -1)
        {
            counter++;
            if(counter == MAX_TRIES)
            {
                if(flag_d)
                {
                    printf("\n");
                    printf("Impossível comunicar com o servidor de raízes, após %d tentativas\n", MAX_TRIES);
                    printf("A terminar o programa...\n");
                    return 1;
                }
            }
        }
    }
    else if(!strcasecmp(buffer, "status\n"))
    {
        //Apresentar:
        //Identificação da stream
        printf("StreamID: %s\n", streamID);

        //Indicação se está interrompido
        if(is_flowing)
        {
            printf("A stream está a correr\n");
        }
        else
        {
            printf("Stream interrompida\n");
        }

        //Indicação se a aplicação é raiz
        if(is_root)
        {
            printf("I am Root!\n");

            //Endereço IP e porto UDP do servidor de acesso se for raiz
            printf("Servidor de acesso: %s:%s\n", ipaddr, uport);

        }
        else
        {
            printf("I am not Root!\n");
            //Endereço IP e porto TCP do ponto de acesso onde está ligado a montante, se não for raiz
            printf("Ligação a montante ao par com o endereço: %s:%s\n", pop_addr, pop_tport);
        }

        //Endereço IP e porto TCP do ponto de acesso disponibilizado
        printf("Ponto de ligação disponibilizado: %s:%s\n", ipaddr, tport);


        //Número de sessões TCP suportadas a jusante e indicação de quantas se encontram ocupadas
        printf("%d sessões TCP suportadas a jusante, das quais %d se encontram ocupadas!\n", tcp_sessions, tcp_occupied);

        //Endereço IP e porto TCP dos pontos de acesso dos pares imediatamente a jusante
        if(redirect_queue_head != NULL)
            printf("Endereços IP e portos TCP dos pontos de acesso dos pares imediatamente a jusante:\n");

        while(redirect_queue_head != NULL)
        {
            printf("%s:%s\n", getIP(redirect_queue_head), getPORT(redirect_queue_head));
            redirect_queue_head = getNext(redirect_queue_head);
        }
    }
    else if(!strcasecmp(buffer, "display on\n"))
    {
        printf("Display on\n");
        flag_b = 1;
    }
    else if(!strcasecmp(buffer, "display off\n"))
    {
        printf("Display off\n");
        flag_b = 0;
    }
    else if (!strcasecmp(buffer, "format ascii\n"))
    {
        printf("Alteração para o formato ascii efetuada\n");
        ascii = 1;
    }
    else if(!strcasecmp(buffer, "format hex\n"))
    {
        printf("Alteração para o formato hexadecimal efetuada\n");
        ascii = 0;
    }
    else if(!strcasecmp(buffer, "debug on\n"))
    {
        flag_d = 1;
        printf("Debug on\n");
    }
    else if(!strcasecmp(buffer, "debug off\n"))
    {
        printf("Debug off\n");
        flag_d = 0;
    }
    else if(!strcasecmp(buffer, "tree\n"))
    {
        if(is_root)
        {
            //Apresentar estrutura da transmissão
            if(tcp_occupied == 0)
            {
                printf("Estrutura de transmissão em árvore\n");

                printf("%s\n", streamID);
                printf("%s:%s (%d)\n", ipaddr, tport, tcp_sessions);
            }
            else
            {
                //meter flag global a 1 e na interface_root se tiver flag ativa chamar função q envia tree query aos filhos
                flag_tree = 1;
            }
        }
        else
        {
            printf("O comando tree apenas funciona para a raíz\n");
        }

    }
    else if(!strcasecmp(buffer, "exit\n"))
    {
        printf("A aplicação irá ser terminada...\n");
        return 1;
    }
    else
    {
        printf("Comando inválido!\n");
    }

    return 0;
}*/