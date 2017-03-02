#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//#include <sys/cstdlib.h> // Para o clear


/*
 * Servidor UDP
 */
main(int argc, char *argv[] )
{
    
    unsigned short port;
   int sockint,s, namelen, client_address_size;
   struct sockaddr_in client, server;
   char buf[200];
   char exitFlag = "n";

   /*
    * Cria um socket UDP (dgram). 
    */
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }

   /*
    * Define a qual endere�o IP e porta o servidor estar� ligado.
    * Porta = 0 -> faz com que seja utilizada uma porta qualquer livre.
    * IP = INADDDR_ANY -> faz com que o servidor se ligue em todos
    * os endere�os IP
    */
    
    port = (unsigned short) atoi(argv[1]);// ******* Cast para short da Porta Digitada
    
    
   server.sin_family      = AF_INET;   /* Tipo do endere�o             */
    server.sin_port        = htons(port);         /* Escolhe uma porta dispon�vel */
   server.sin_addr.s_addr = INADDR_ANY;/* Endere�o IP do servidor      */

    
   /*
    * Liga o servidor � porta definida anteriormente.
    */
   if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
   {
       perror("bind()");
       exit(1);
   }

   /* Consulta qual porta foi utilizada. */
   namelen = sizeof(server);
   if (getsockname(s, (struct sockaddr *) &server, &namelen) < 0)
   {
       perror("getsockname()");
       exit(1);
   }

   /* Imprime qual porta foi utilizada. */
   printf("Porta utilizada � %d\n", ntohs(server.sin_port));

   /*
    * Recebe uma mensagem do cliente.
    * O endere�o do cliente ser� armazenado em "client".
    */
   client_address_size = sizeof(client);

   while(buf != "exit")
   {

     if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &client,
              &client_address_size) <0)
     {
         perror("recvfrom()");
         exit(1);
     }
      system("CLS");
      printf("SERVIDOR:\n");
     /*
      * Imprime a mensagem recebida, o endere�o IP do cliente
      * e a porta do cliente 
      */
     printf("Recebida a mensagem: %s \n IP: %s PORTA: %d\n",buf,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
   /*
    * Fecha o socket.
    */
   }
   close(s);
 
 exit(1);
}
