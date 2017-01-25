////////////////////////////////////////////////////////////////////////////////
//                              Projeto SO                                    //
//               Sistemas Operativos, DEI/IST/ULisboa 2016-17                 //
//                               Grupo 60                                     //
//                        Ricardo Oliveira, 84759                             //
//                        Ricardo Martins,  84761                             //
////////////////////////////////////////////////////////////////////////////////

#include "commandlinereader.h"
#include "contas.h"

#include <signal.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

#define MAXARGS 4
#define BUFFER_SIZE 100

#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_TRANSFERIR "transferir"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"
#define COMANDO_SAIR_TERMINAL "sair-terminal"
#define AGORA "agora"

#define CREDITAR   0
#define DEBITAR    1
#define TRANSFERIR 2
#define LER_SALDO  3
#define SIMULAR    4
#define SAIR       5

#define NUM_PROC_FILHO 20

#define NUM_TRABALHADORAS 3
#define CMD_BUFFER_DIM (NUM_TRABALHADORAS * 2)

typedef struct {
    int operacao;
    int idConta;
    int idDestino;
    int valor;
    int numAnos;
    int PID;
    int flag_sair_agora;
} comando_t;

comando_t cmd_buffer[CMD_BUFFER_DIM];

time_t start_t, end_t;
double diff_t;

int  fid;
int  fifo2;
char str[64];
char pipeID[30];

int main (int argc, char** argv) {

    char *args[MAXARGS + 1];
    char buffer[BUFFER_SIZE];

    /* Cria o pipe */

    sprintf(pipeID, "i-banco-tunnel-%d", getpid()); /* Criacao do nome do pipe conforme o pid*/
    if (mkfifo(pipeID, 0666) < 0)
        perror("Pipe Creating Error");

    int fifo = open("i-banco-pipe", O_WRONLY); /* Abertura do i-banco-pipe */

    /* Inicializa o signal */

    if (signal(SIGPIPE, muda_SIG2) == SIG_ERR) {
        perror("Erro ao definir signal.");
    } /* Associa um signal a rotina que o trata */

    /* Inicia Banco */

    printf("Bem-vinda/o ao i-banco\n\n");

    inicializarContas();

    while (1) { /* O i-banco-terminal recebe input atraves do terminal e testa-se a operacao realizada */

        int numargs;
        numargs = readLineArguments(args, MAXARGS+1, buffer, BUFFER_SIZE);

        if (numargs < 0 ||
            (numargs > 0 && (strcmp(args[0], COMANDO_SAIR) == 0))) {

            comando_t info;

            if ((numargs == 2) && (strcmp(args[1], AGORA) == 0)) {

                info.flag_sair_agora = 1;

            } /* Comando "sair agora"*/

            info.operacao = SAIR;
            info.PID = getpid();

            write(fifo, &info, sizeof(comando_t)); /* Envia a informacao para o i-banco atraves do i-banco-pipe*/

        } /* EOF (end of file) do stdin ou comando "sair" */

        else if ((strcmp(args[0], COMANDO_SAIR_TERMINAL) == 0)) {

            printf("--\ni-banco-terminal vai terminar.\n");

            close(fifo2); /* Fecha o pipe */
            unlink(pipeID); /* Remove o pipe */

            exit(EXIT_SUCCESS);
        } /* Comando "sair-terminal" */

        else if (numargs == 0) {
            continue;
        } /* Nenhum argumento; ignora e volta a pedir */

        else if (strcmp(args[0], COMANDO_DEBITAR) == 0) {
            comando_t info;

            if (numargs < 3) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_DEBITAR);
	            continue;
            } /* Poucos argumentos */

            if (atoi(args[2]) <= 0) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_DEBITAR);
                continue;
            } /* Verifica a validez do valor */

            if(!contaExiste(atoi(args[1]))) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_DEBITAR);
                continue;
            } /* Verifica a existencia da conta */

            /* Cria estrutura comando_t para colocar no buffer */
            info.operacao = DEBITAR;
            info.idConta = atoi(args[1]);
            info.valor = atoi(args[2]);
            info.PID = getpid();

            write(fifo, &info, sizeof(comando_t)); /* Coloca a estrutura criada no buffer */

            time(&start_t); /* Inicia a contagem de tempo */

            sprintf(pipeID, "i-banco-tunnel-%d", getpid()); /* Criacao do nome do pipe conforme o pid */
            if ((fifo2 = open(pipeID, O_RDONLY)) < 0) {
                perror("Opening Tunnel Error");
            } /* Abertura do pipe de comunicacao */

            read(fifo2, str, 64); /* Le a mensagem do i-banco */

            time(&end_t); /* Termina a contagem de tempo */
            diff_t = difftime(end_t, start_t); /* Calcula o tempo de execucao */

            printf("%s", str);
            printf("Tempo de execucao = %f\n", diff_t);

            close(fifo2); /* Fecha o pipe */
        } /* Comando "Debitar" */

        else if (strcmp(args[0], COMANDO_CREDITAR) == 0) {
            comando_t info;

            if (numargs < 3) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_CREDITAR);
                continue;
            } /* Poucos argumentos */

            if (atoi(args[2]) <= 0) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_CREDITAR);
                continue;
            } /* Verifica a validez do valor */

            if(!contaExiste(atoi(args[1]))) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_CREDITAR);
                continue;

            } /* Verifica a existencia da conta */
            /* Cria estrutura comando_t para colocar no buffer */
            info.operacao = CREDITAR;
            info.idConta = atoi(args[1]);
            info.valor = atoi(args[2]);
            info.PID = getpid();

            write(fifo, &info, sizeof(comando_t)); /* Coloca a estrutura criada no buffer */
            time(&start_t); /* Inicia a contagem de tempo */

            sprintf(pipeID, "i-banco-tunnel-%d", getpid()); /* Criacao do nome do pipe conforme o pid */
            if ((fifo2 = open(pipeID, O_RDONLY)) < 0) {
                perror("Opening Tunnel Error");
            } /* Abertura do pipe de comunicacao */

            read(fifo2, str, 64); /* Le a mensagem do i-banco */

            time(&end_t); /* Termina a contagem de tempo */
            diff_t = difftime(end_t, start_t); /* Calcula o tempo de execucao */

            printf("%s", str);
            printf("Tempo de execucao = %f\n", diff_t);

            close(fifo2); /* Fecha o pipe */
        } /* Comando "Creditar" */

        else if (strcmp(args[0], COMANDO_TRANSFERIR) == 0) {
            comando_t info;

            if (numargs < 4) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_TRANSFERIR);
                continue;
            } /* Poucos argumentos */

            if (atoi(args[3]) <= 0) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_TRANSFERIR);
                continue;
            } /* Verifica a validez do valor */

            if (!contaExiste(atoi(args[1])) || !contaExiste(atoi(args[2]))) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_TRANSFERIR);
                continue;
            } /* Verifica a existencia da conta */

            /* Cria estrutura comando_t para colocar no buffer */
            info.operacao = TRANSFERIR;
            info.idConta = atoi(args[1]);
            info.idDestino = atoi(args[2]);
            info.valor = atoi(args[3]);
            info.PID = getpid();

            write(fifo, &info, sizeof(comando_t)); /* Coloca a estrutura criada no buffer */

            time(&start_t); /* Inicia a contagem de tempo */

            sprintf(pipeID, "i-banco-tunnel-%d", getpid()); /* Criacao do nome do pipe conforme o pid */
            if ((fifo2 = open(pipeID, O_RDONLY)) < 0) {
                perror("Opening Tunnel Error");
            } /* Abertura do pipe de comunicacao */

            read(fifo2, str, 64); /* Le a mensagem do i-banco */

            time(&end_t); /* Termina a contagem de tempo */
            diff_t = difftime(end_t, start_t); /* Calcula o tempo de execucao */

            printf("%s", str);
            printf("Tempo de execucao = %f\n", diff_t);

            close(fifo2); /* Fecha o pipe */
        } /* Comando "Creditar" */

        else if (strcmp(args[0], COMANDO_LER_SALDO) == 0) {
            comando_t info;

            if (numargs < 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_LER_SALDO);
                continue;
            } /* Poucos argumentos */

            if(!contaExiste(atoi(args[1]))) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_LER_SALDO);
                continue;
            } /* Verifica a existencia da conta */

            /* Cria estrutura comando_t para colocar no buffer */
            info.operacao = LER_SALDO;
            info.idConta = atoi(args[1]);
            info.PID = getpid();

            write(fifo, &info, sizeof(comando_t)); /* Coloca a estrutura criada no buffer */

            time(&start_t); /* Inicia a contagem de tempo */

            sprintf(pipeID, "i-banco-tunnel-%d", getpid()); /* Criacao do nome do pipe conforme o pid */
            if ((fifo2 = open(pipeID, O_RDONLY)) < 0) {
                perror("Opening Tunnel Error");
            } /* Abertura do pipe de comunicacao */

            read(fifo2, str, 64); /* Le a mensagem do i-banco */

            time(&end_t); /* Termina a contagem de tempo */
            diff_t = difftime(end_t, start_t); /* Calcula o tempo de execucao */

            printf("%s", str);
            printf("Tempo de execucao = %f\n", diff_t);

            close(fifo2); /* Fecha o pipe */
        } /* Comando "Ler Saldo" */

        else if (strcmp(args[0], COMANDO_SIMULAR) == 0) {
            comando_t info;


            if (numargs < 2 || atoi(args[1]) < 0) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_SIMULAR);
                continue;
            } /* Poucos argumentos */

            else {
                info.operacao = SIMULAR;
                info.numAnos = atoi(args[1]);
                info.PID = getpid();

                write(fifo, &info, sizeof(comando_t));

            }
        }
        else {
            printf("Comando desconhecido. Tente de novo.\n");
        } /* Comando nao existente ou com erros de escrita */

    } /* Termina o ciclo while que mantem o programa a correr */
} /* Fim da Tarefa Inicial */
