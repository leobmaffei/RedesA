#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
//#include <sys/cstdlib.h> // Para o clear

/*
 * Cliente UDP
 */
main(argc, argv)
int argc;
char **argv;
{


   int sockint,s, sResposta, namelen, client_address_size; //neste caso o endereco do cliente é o servidor
   unsigned short port, portResposta;
   struct sockaddr_in client, server;
   char buf[200];
   char input[200] = "exit\n";  //Adicionado o \n para comparacao Show mano
   /* 
    * O primeiro argumento (argv[1]) é o endereço IP do servidor.
    * O segundo argumento (argv[2]) é a porta do servidor.
    */
   if(argc != 3)
   {
      printf("Use: %s enderecoIP porta\n",argv[0]);
      exit(1);
   }
  port = htons(atoi(argv[2]));
  //portResposta = htons(atoi("5454"));
  
   /*
    * Cria um socket UDP (dgram).
    */
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }
   if ((sResposta = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }
  

   /* Define o endereço IP e a porta do servidor */
   server.sin_family      = AF_INET;            /* Tipo do endereço         */
   server.sin_port        = port;               /* Porta do servidor        */
   server.sin_addr.s_addr = inet_addr(argv[1]); /* Endereço IP do servidor  */
    
    client.sin_family = AF_INET;
    client.sin_port = port;
    client.sin_addr.s_addr = INADDR_ANY;
    client_address_size = sizeof(client);

    while(strcmp(buf,input) != 0) {
   //strcpy(buf, "Hello");

   /*Pega a mensagem do teclado para ser enviada*/

      printf(">");
      fgets(buf, sizeof buf, stdin);


    /* Envia a mensagem no buffer para o servidor */
      if (sendto(s, buf, (strlen(buf)+1), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
      {
          perror("sendto()");
          exit(2);
      }
          
      


          //daqui para baixo ele vira o servidor esperando a resposta
     
     /*
    * Recebe uma mensagem do cliente.
    * O endereço do cliente será armazenado em "client".
    */
     
        //int recived = 0;
        
        
    if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &client,
      &client_address_size) <0)
     {
       perror("recvfrom()");
       exit(1);
     }
            
      /*
      * Imprime a mensagem recebida, o endereço IP do cliente
      * e a porta do cliente 
      */
     printf("Recebida a mensagem: %s \n IP: %s PORTA: %d\n",buf,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
       

    }
      /* Fecha o socket */
      
      close(s);
    exit(1);
}
