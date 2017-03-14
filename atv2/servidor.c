#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


struct dados 
{
  char usuario[19];
  char msg[79];
  int controle;
  int aux; 
}envia, vet[10], vet2[10];


/*
 * Servidor TCP
 */
main(argc, argv)
int argc;
char **argv;
{
    unsigned short port;                     
    struct sockaddr_in client; 
    struct sockaddr_in server; 
    int s;                     /* Socket para aceitar conexıes       */
    int ns;                    /* Socket conectado ao cliente        */
    int namelen;       
    int i;
    int cont = 0;
    int cont2 = 0; // para deletar mensagens
    

    /*
     * O primeiro argumento (argv[1]) È a porta
     * onde o servidor aguardar· por conexıes
     */
    if (argc != 2)
    {
        fprintf(stderr, "Use: %s porta\n", argv[0]);
        exit(1);
    }

   
    port = (unsigned short) atoi(argv[1]);

   
    
    /*
     * Cria um socket TCP (stream) para aguardar conexıes
     */
    if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket()");
        exit(2);
    }

  
  
  /*
    * Define a qual endereÁo IP e porta o servidor estar· ligado.
    * IP = INADDDR_ANY -> faz com que o servidor se ligue em todos
    * os endereÁos IP
    */
    server.sin_family = PF_INET;   
    server.sin_port   = htons(port);       
    server.sin_addr.s_addr = INADDR_ANY;


    /*
     * Liga o servidor ‡ porta definida anteriormente.
     */

    printf("Server UP! porta utilizada: %d\n",ntohs(server.sin_port));

    if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
       perror("Bind()");
       exit(3);
    }

    
    

    /*
     * Prepara o socket para aguardar por conexıes e
     * cria uma fila de conexıes pendentes.
     */
    if (listen(s, 1) != 0)
    {
        perror("Listen()");
        exit(4);
    }

    


    /*
     * Aceita uma conex„o e cria um novo socket atravÈs do qual
     * ocorrer· a comunicaÁ„o com o cliente.
     */
    namelen = sizeof(client);

    if ((ns = accept(s, (struct sockaddr *)&client, &namelen)) == -1)
    {
        perror("Accept()");
        exit(5);
    }


    printf("Conectado com cliente de IP:%s  pela porta: %d \n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

    
    do{
      
	/* Recebe uma mensagem do cliente atraves do novo socket conectado */
	if (recv(ns, &envia, sizeof(envia), 0) == -1)
	{
	    perror("Recv()");
	    exit(6);
	}
   

   //verifica a opcao escolhida pelo cliente
	if(envia.controle == 1)
    {
           printf("Comando: Cadastrar Mensagem\n");
           if(cont < 10)
           {
                for(i = 0; i < 10; i++)
                    if(vet[i].aux == 0)
                        break; 
                        
                strcpy(vet[i].msg,envia.msg);
                strcpy(vet[i].usuario,envia.usuario);
                vet[i].aux = 1;
               
	            cont++;
               

                strcpy(envia.msg,"Mensagem cadastrada com Sucesso!");
               
                /* Envia uma mensagem ao cliente atravÈs do socket conectado */
		        if (send(ns, &envia, sizeof(envia), 0) < 0)
		        {
		            perror("Send()");
		            exit(7);
		        }
           }
           else
           {
                strcpy(envia.msg,"Erro: maximo de mensagens cadastradas");
               
                if (send(ns, &envia, sizeof(envia), 0) < 0)
		        {
		            perror("Send()");
		            exit(7);
		        }
           }   
    }
    else
	if(envia.controle == 2)
    {
        printf("Comando: Ler Mensagens\n");
        for (i = 0; i < 10; i++)
        {
            vet[i].controle = cont;
	       
	        if(vet[i].aux == 1)
                if (send(ns, &vet[i], sizeof(vet[i]), 0) < 0)
		        {
		            perror("Send()");
		            exit(7);
		        }
         }
         printf("Mensagens enviadas para o cliente\n");
    }
    else
	if(envia.controle == 3)
    {
        printf("Comando: Apagar mensagens\n");
        for(i = 0; i < 10; i++)
        {
            if(strcmp(vet[i].usuario,envia.usuario) == 0)
            {
                vet[i].aux = 0;
                strcpy(vet2[cont2].usuario,vet[i].usuario);
                strcpy(vet2[cont2].msg,vet[i].msg);
                cont--;
                cont2++;
            }
        }
        
        vet2[0].aux = cont2;
        
        if(cont2 > 0)
            printf("Mensagens apagadas com sucesso!\n");
        else
            printf("Não existem mensagens para apagar\n");
        
        for(i = 0; i < cont2; i++)
        {
            if (send(ns, &vet2[i], sizeof(vet2[i]), 0) < 0)
	        {
	            perror("Send()");
	            exit(7);
	        }
        }
        cont2 = 0;
    }

    }while(envia.controle != 4);
    
    
    /* Fecha o socket conectado ao cliente */
    close(ns);



    /* Fecha o socket aguardando por conexıes */
    close(s);

    exit(0);
}

