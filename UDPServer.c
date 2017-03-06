#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
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
  char bufResposta[2000];
  char exitFlag = "n";
  int flagComandoSistema; 
/*
    * Define a qual endereço IP e porta o servidor estará ligado.
    * Porta = 0 -> faz com que seja utilizada uma porta qualquer livre.
    * IP = INADDDR_ANY -> faz com que o servidor se ligue em todos
    * os endereços IP
    */

    port = (unsigned short) atoi(argv[1]);// ******* Cast para short da Porta Digitada
    
   server.sin_family      = AF_INET;   /* Tipo do endereço             */
    server.sin_port        = htons(port);         /* Escolhe uma porta disponível */
   server.sin_addr.s_addr = INADDR_ANY;/* Endereço IP do servidor      */
    system("clear");
   /*
    * Cria um socket UDP (dgram). 
    */
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
     perror("socket()");
     exit(1);
   }

   /*
    * Liga o servidor à porta definida anteriormente.
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
   printf("Server UP! Porta utilizada: %d\n\n", ntohs(server.sin_port));

   /*
    * Recebe uma mensagem do cliente.
    * O endereço do cliente será armazenado em "client".
    */
   client_address_size = sizeof(client);

   while(1)
   {

     if(recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *) &client,
      &client_address_size) <0)
     {
       perror("recvfrom()");
       exit(1);
     }
     //system(buf);

      //cria um arquivo para guardar o retorno do system
     FILE *fp;
     char path[200];
        //zera o buff resposta para nao repetir mensagens
     strcpy(bufResposta, "");

      /* Open the command for reading. */
     fp = popen(buf, "r");
     if (fp == NULL) {
      printf("Failed to run command\n" );
      exit(1);
    }

      /*
      * Imprime a mensagem recebida, o endereço IP do cliente
      * e a porta do cliente 
      */

    printf("\nRecebida a mensagem: %s IP: %s PORTA: %d\n",buf,inet_ntoa(client.sin_addr),ntohs(client.sin_port));

   //garda o retorno da função no buffer de resposta

     /* Read the output a line at a time - output it. */
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
      strcat(bufResposta, path);
      //printf("%s", bufResposta);
    }

/* Envia a mensagem no buffer para o servidor */
    if (sendto(s, bufResposta, (strlen(bufResposta)+1), 0, (struct sockaddr *)&client, sizeof(client)) < 0)
    {
      perror("sendto()");
      exit(2);
    }

    /* close */
    pclose(fp);
   /* Fecha o socket */ 
  }
  close(s);
  exit(1);
}
