/*
  REDES A ATIVIDADE 2
  ALUNOS:
  Erich Silveira      13005780
  Leonardo Maffei   11742236
  Leonardo Possi    13160817
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


void menu();

/*
 * Cliente TCP
 */

struct mensagem
{
  char usuario[19];
  char msg[79];
  int tipo;
  int aux;
}envia;

    struct hostent *hostnm;    
    struct sockaddr_in server; 
    int s;  
    
    int opcao;
    int cont = 0;
    int cont2 = 0;
    char usuario[10];
    char msg[50];

main(argc, argv)
int argc;
char **argv;
{
    unsigned short port;                    
    


    /*
     * O primeiro argumento (argv[1]) é o hostname do servidor.
     * O segundo argumento (argv[2]) é a porta do servidor.
     */
    if (argc != 3)
    {
        fprintf(stderr, "Use: %s hostname porta\n", argv[0]);
        exit(1);
    }

    /*
     * Obtendo o endereço IP do servidor
     */
   
    hostnm = gethostbyname(argv[1]);
    
    
    if (hostnm == (struct hostent *) 0)
    {
        fprintf(stderr, "Gethostbyname failed\n");
        exit(2);
    }
   
   
    port = (unsigned short) atoi(argv[2]);

   
    
    /*
     * Define o endereço IP e a porta do servidor
     */
    server.sin_family      = PF_INET;
    server.sin_port        = htons(port);
    server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr);

   
    
    /*
     * Cria um socket TCP (stream)
     */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(3);
    }

   
   
   /* Estabelece conexão com o servidor */
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connect()");
        exit(4);
    }
    
    do{
       menu();
    }while (1 == 1);

  
    /* Fecha o socket */
    close(s);

    printf("Cliente terminou com sucesso\n");
    exit(0);

}

void menu()
{
            printf("\nOpcoes:\n");
            printf("1 - Cadastrar mensagem\n");
            printf("2 - Ler mensagens\n");
	       printf("3 - Apagar mensagens\n");
            printf("4 - Sair da aplicacao\n");
            printf("OP >");
            scanf("%d",&opcao);
  
      if(opcao==1){
	    fpurge(stdin);
	    
	    printf("\nUsuario: ");
        fgets(usuario, sizeof usuario, stdin);
	    
	    fpurge(stdin);
	    
	    printf("\nMensagem: ");
        fgets(msg, sizeof msg, stdin);
	    
	    fpurge(stdin);
	    
	    strcpy(envia.usuario,usuario);
	    strcpy(envia.msg,msg);
	    
	    envia.tipo = 1;
	
	    /* Envia mensagem no buffer para o servidor */
	    if (send(s, &envia, sizeof(envia), 0) < 0)
	    {
		perror("Send()");
		exit(5);
	    }
	    
	    /* Recebe a mensagem do servidor no buffer */
	    if (recv(s, &envia, sizeof(envia), 0) < 0)
	    {
		perror("Recv()");
		exit(6);
	    }else{

        printf("%s\n", envia.msg);

        }
        

      }
	    
      if(opcao==2){
	
	    envia.tipo = 2;
	    
	    /* Envia mensagem no buffer para o servidor */
	    if (send(s, &envia, sizeof(envia), 0) < 0)
	    {
		perror("Send()");
		exit(5);
	    }
	    
	    /* Recebe a mensagem do servidor no buffer */
	    if (recv(s, &envia, sizeof(envia), 0) < 0)
	    {
		perror("Recv()");
		exit(6);
	    }
	    
	    if(envia.tipo > 0)
        {
            cont = envia.tipo;
            
            printf("\nNumero de mensagens cadastradas: %d",cont);

            do
            {
                printf("\nUsuario: %s   Mensagem: %s", envia.usuario, envia.msg);
    
                cont--;
    
                if(cont > 0)
                {
                    /* Recebe a mensagem do servidor no buffer */
				    if (recv(s, &envia, sizeof(envia), 0) < 0)
				    {
				        perror("Recv()");
				        exit(6);
				    }
                }
                            
            }while(cont > 0);
        }
        else
            printf("Servidor sem mensagens\n");
		    
      }
      
    if(opcao==3){
      
            envia.tipo = 3;
            
            fpurge(stdin);
	    
	        printf("\nUsuario: ");
            fgets(usuario, sizeof usuario, stdin);
        
	        strcpy(envia.usuario,usuario);
	    
	        /* Envia a mensagem no buffer para o servidor */
	        if (send(s, &envia, sizeof(envia), 0) < 0)
	        {
		        perror("Send()");
		        exit(5);
	        }
	        
	        if (recv(s, &envia, sizeof(envia), 0) < 0)
	        {
		        perror("Recv()");
		        exit(6);
	        }
	        
	        if(envia.aux > 0)
            {
                cont2 = envia.aux;
                
                printf("\nNumero de mensagens apagadas: %d",cont2);

                do
                {
                    printf("\nUsuario: %s   Mensagem: %s", envia.usuario, envia.msg);
        
                    cont2--;
        
                    if(cont2 > 0)
                    {
                        /* Recebe a mensagem do servidor no buffer*/
				        if (recv(s, &envia, sizeof(envia), 0) < 0)
				        {
				            perror("Recv()");
				            exit(6);
				        }
                    }
                                
                }while(cont2 > 0);
            }
            else
                printf("\nNao foi apagada nenhuma mensagem do usuario: %s",usuario);
	
    }
	if(opcao==4)
	  {
      envia.tipo = 4;
         if (send(s, &envia, sizeof(envia), 0) < 0)
        {
        perror("Send()");
        exit(5);
        }

        close(s);

         exit(1);
	  }
	   	    
     }



