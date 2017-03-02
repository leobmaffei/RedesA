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


   int s;
   unsigned short port;
   struct sockaddr_in server;
   char buf[200];
   char input[200] = "exit\n";  //Adicionado o \n para comparacao
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
  while(strcmp(buf,input) != 0) {
   /*
    * Cria um socket UDP (dgram).
    */
   if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
   {
       perror("socket()");
       exit(1);
   }

   /* Define o endereço IP e a porta do servidor */
   server.sin_family      = AF_INET;            /* Tipo do endereço         */
   server.sin_port        = port;               /* Porta do servidor        */
   server.sin_addr.s_addr = inet_addr(argv[1]); /* Endereço IP do servidor  */

   //strcpy(buf, "Hello");

   /*Pega a mensagem do teclado para ser enviada*/

      printf(">");
      fgets(buf, sizeof buf, stdin);
      //teste para ver o erro -------------------------------------------------
      
      
    if(strcmp(buf,input) == 0){
      printf("igual\n");
    }
    if(strcmp(buf,input) != 0){
      printf("diferente\n");
    }
//------------------------------------------------------------------------------

    /* Envia a mensagem no buffer para o servidor */
      if (sendto(s, buf, (strlen(buf)+1), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
      {
          perror("sendto()");
          exit(2);
      }
          close(s);
   /* Fecha o socket */
      }

      
    exit(1);
}
