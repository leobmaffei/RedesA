#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Cliente TCP
 */
main(argc, argv)
int argc;
char **argv;
{
    unsigned short port;       
    char sendbuf[12];              
    char recvbuf[12];              
    struct hostent *hostnm;    
    struct sockaddr_in server; 
    int s; 
    int op;                    


    struct mensagem
    {
      char usuario[19];
      char texto[79];
      char comando[10];
    };


    /*
     * O primeiro argumento (argv[1]) � o hostname do servidor.
     * O segundo argumento (argv[2]) � a porta do servidor.
     */
    if (argc != 3)
    {
        fprintf(stderr, "Use: %s hostname porta\n", argv[0]);
        exit(1);
    }

    /*
     * Obtendo o endere�o IP do servidor
     */
    hostnm = gethostbyname(argv[1]);
    if (hostnm == (struct hostent *) 0)
    {
        fprintf(stderr, "Gethostbyname failed\n");
        exit(2);
    }
    port = (unsigned short) atoi(argv[2]);

    /*
     * Define o endere�o IP e a porta do servidor
     */
    server.sin_family      = AF_INET;
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

    /* Estabelece conex�o com o servidor */
    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        perror("Connect()");
        exit(4);
    }

    while(op!=4){

        //menu
    printf("Selecione a opcao desejada:\n");
    printf("1 - Cadastrar Mensagem\n");
    printf("2 - Ler Mensagens\n");
    printf("3 - Apagar Mensagens\n");
    printf("4 - Sair da Aplicacao\n\n");
    printf("Opcao: "); 
 
    scanf("%d", &op);               //Le a opcao escolhida pelo usuario
    printf("\n\n");

    switch(op){


        case 1:{ //cadastrar mensagem

            printf("Cadastrar Mensagem:\n\n");
            printf("Usu�rio:");
            scanf("%s"mensagem.usuario);
            printf("Mensagem:"mensagem.texto);



        }

        case 2:{ // Ler mensagens


        }

        case 3:{ // Apagar mensagens 



        }




    }


    }

    







    strcpy(sendbuf, "Requisi��o");

    /* Envia a mensagem no buffer de envio para o servidor */
    if (send(s, sendbuf, strlen(sendbuf)+1, 0) < 0)
    {
        perror("Send()");
        exit(5);
    }
    printf("Mensagem enviada ao servidor: %s\n", sendbuf);

    /* Recebe a mensagem do servidor no buffer de recep��o */
    if (recv(s, recvbuf, sizeof(recvbuf), 0) < 0)
    {
        perror("Recv()");
        exit(6);
    }
    printf("Mensagem recebida do servidor: %s\n", recvbuf);

    /* Fecha o socket */
    close(s);

    printf("Cliente terminou com sucesso.\n");
    exit(0);

}


