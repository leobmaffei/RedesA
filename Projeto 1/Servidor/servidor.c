/*
  REDES A ATIVIDADE 6
  ALUNOS:
  Erich Silveira      13005780
  Leonardo Maffei   11742236
  Leonardo Possi    13160817
*/


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <sys/sem.h>            /* for semget(), semop(), semctl() */




#define PROTECT
#define SEM_KEY   0x1243




struct sembuf g_sem_op1[1];
struct sembuf g_sem_op2[1];





int cont = 0;
int cont2 = 0;
int g_sem_id;


int temperatura[10];
int conexao = 0;
int clientNumber = 0;

int flagLed = 0;


struct dados 
{
  char usuario[19];
  char msg[79];
  int controle;
  int aux; 
}envia, vet[10], vet2[10];


// função para a thread 
void* tratarCliente(void *);
void* tratarMobile(void *);
void* logicaServer(void *);



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
    //int cont = 0;
    //int cont2 = 0; // para deletar mensagens

    pthread_t thread_id;
    int tStatus;





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



      //cria thread da logica do server
     tStatus = pthread_create(&thread_id, NULL, &logicaServer, 0); /* Print o’s continuously to stderr. */
    if(tStatus !=0){

      printf("Nao foi possivel criar thread\n");
      exit(6);
    }
       
    
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

    
    while(1){
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



    /* Recebe uma mensagem do cliente atraves do novo socket conectado */
  if (recv(ns, &conexao, sizeof(int), 0) == -1)
  {
      perror("Recv()");
      exit(6);
      
  }

printf("CONEXAOOO >>>%d\n",conexao );

 if(conexao == 1){

   // Cria thread para atnder cliente arduino
    tStatus = pthread_create(&thread_id, NULL, &tratarCliente, &ns); /* Print o’s continuously to stderr. */
    if(tStatus !=0){

      printf("Nao foi possivel criar thread\n");
      exit(6);
    }
    printf("CONEXAO 1\n");
    conexao = 0;

    printf("Conectado com cliente de IP:%s  pela porta: %d \n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
 }else{
  // Cria thread para atnder cliente mobile
    tStatus = pthread_create(&thread_id, NULL, &tratarMobile, &ns); /* Print o’s continuously to stderr. */
    if(tStatus !=0){

      printf("Nao foi possivel criar thread\n");
      exit(6);
    }

    printf("CONEXAO N\n");

    printf("Conectado com cliente de IP:%s  pela porta: %d \n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

 }

   

 
    //pthread_detach(thread); 


} //fecha do while infinito 


    /* Fecha o socket aguardando por conexıes */
    close(s);

    exit(0);
}








void* tratarCliente(void *clientSock){

  int i;
  int clientID;
  int ns = *(int*)clientSock;
  char ledOp = '1';



    clientID = clientNumber;
    clientNumber++;


while(1){
      
  /* Recebe uma mensagem do cliente atraves do novo socket conectado */
  if (recv(ns, &temperatura[clientID], sizeof(int), 0) == -1)
  {
      perror("Recv()");
      exit(6);
      
  }
   




  printf("%d <- Temperatura cliente %d\n",temperatura[clientID],clientID);


  }



}



void* tratarMobile(void *clientSock){

  int i;
  int clientID;
  int ns = *(int*)clientSock;
  char ledOp = '1';

  char recebido = 'a';

    clientID = clientNumber;
    clientNumber++;


while(1){
      
  /* Recebe uma mensagem do cliente atraves do novo socket conectado */
  if (recv(ns, &recebido, sizeof(char), 0) == -1)
  {
      perror("Recv()");
      exit(6);
      
  }
   




  printf("%c <- CHAR RECEBIDO\n",recebido);



  }

}




void* logicaServer(void *clientSock){

 printf("LOGICA SERVER CRIADO\n");


  }















