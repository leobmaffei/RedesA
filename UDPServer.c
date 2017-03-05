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
  char bufResposta[200];
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

    while(buf != "exit")
    {
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
     printf("Server UP. Porta utilizada é %d\n", ntohs(server.sin_port));

   /*
    * Recebe uma mensagem do cliente.
    * O endereço do cliente será armazenado em "client".
    */
     client_address_size = sizeof(client);


      //system("clear");

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

    /*
    * Fecha o socket.
    */

     //close(s);
     //printf("fexando socket de recebimento\n");
     // removido o atoi pois acredito nao precisar pois ja está em int
     //port = client.sin_port;
      //printf("porta de envio %s\n", ntohs(port));


     //if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
     //{
       //perror("socket()");
      // exit(1);
    // }
     // printf("sem erro de socket\n");

   /* Define o endereço IP e a porta do servidor */
  // server.sin_family      = AF_INET;            /* Tipo do endereço         */
   //server.sin_port        = port;               /* Porta do servidor        */
   //server.sin_addr.s_addr = inet_addr(inet_ntoa(client.sin_addr)); /* Endereço IP do servidor  */
         //printf("criando tipo, porta e IP\n");

   //garda o retorno da função no buffer de resposta
    // fgets(bufResposta, sizeof(bufResposta), "Teste de resposta ao cliente");
        
          strncpy(bufResposta,"Resposta para cliente",200);
          printf("salva string no bufResposta:  %s\n",bufResposta);

/* Envia a mensagem no buffer para o servidor */
     if (sendto(s, bufResposta, (strlen(bufResposta)+1), 0, (struct sockaddr *)&server, sizeof(server)) < 0)
     {
      perror("sendto()");
      exit(2);
    }
         printf("mensagem retornada para o cliente com sucesso\n");

    close(s);
         printf("porta de resposta fechada\n");

   /* Fecha o socket */ 

  }


  exit(1);
}
