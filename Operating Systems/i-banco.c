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
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAXARGS 4
#define BUFFER_SIZE 100

#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_TRANSFERIR "transferir"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"
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

pthread_t tid[NUM_TRABALHADORAS];
pthread_mutex_t semExMut;
pthread_mutex_t trincoContas[NUM_CONTAS];
pthread_mutex_t trincoOperacoes;
pthread_cond_t condition;

comando_t cmd_buffer[CMD_BUFFER_DIM];
sem_t posicoesVazias, posicoesOcupadas;

int buff_write_idx = 0; /* Indice de escrita do buffer */
int buff_read_idx = 0; /* Indice de leitura do buffer */
int emAtividade = 1; /* Flag que mantem ativa a funcao que trata as tarefas */

int contadorOperacoesAtivas = 0; /* Contador de operacoes ativas ou em espera */

int  fid;
int  fifo2;
char str[64];
char str2[64];
char pipeID[30];

void mutex_lock_semExMut(void) {
  if(pthread_mutex_lock(&semExMut) != 0) {
      perror("Error in pthread_mutex_lock().\n");
      exit(EXIT_FAILURE);
  } /* Caso ocorra algum erro */
} /* Funcao bloqueia trinco semExMut */

void mutex_unlock_semExMut(void) {
  if(pthread_mutex_unlock(&semExMut) != 0) {
      perror("Error in pthread_mutex_unlock().\n");
      exit(EXIT_FAILURE);
  } /* Caso ocorra algum erro */
} /* Funcao desbloqueia trinco semExMut*/

void mutex_lock_trincoOperacoes(void) {
  if(pthread_mutex_lock(&trincoOperacoes) != 0) {
      perror("Error in pthread_mutex_lock().\n");
      exit(EXIT_FAILURE);
  } /* Caso ocorra algum erro */
} /* Funcao bloqueia trinco trincoOperacoes*/

void mutex_unlock_trincoOperacoes(void) {
  if(pthread_mutex_unlock(&trincoOperacoes) != 0) {
      perror("Error in pthread_mutex_unlock().\n");
      exit(EXIT_FAILURE);
  } /* Caso ocorra algum erro */
} /* Funcao desbloqueia trinco trincoOperacoes */

void mutex_lock_trincoContas(int idConta) {
  if(pthread_mutex_lock(&trincoContas[idConta]) != 0) {
      perror("Error in pthread_mutex_lock().\n");
      exit(EXIT_FAILURE);
  } /* Caso ocorra algum erro */
} /* Funcao bloqueia trinco trincoContas */

void mutex_unlock_trincoContas(int idConta) {
  if(pthread_mutex_unlock(&trincoContas[idConta]) != 0) {
      perror("Error in pthread_mutex_unlock().\n");
      exit(EXIT_FAILURE);
  } /* Caso ocorra algum erro */
} /* Funcao desbloqueia trinco trincoContas */

void colocaBuffer(comando_t tarefa) {

    mutex_lock_trincoOperacoes();
    contadorOperacoesAtivas ++; /*Incrementa o numero de operacoes a ocorrer ou em espera */
    mutex_unlock_trincoOperacoes();

    sem_wait(&posicoesVazias); /* Espera por uma posicao vazia */
    mutex_lock_semExMut(); /* Bloqueia o trinco para impedir outra escritura */
    cmd_buffer[buff_write_idx] = tarefa; /* Coloca no buffer */
    buff_write_idx = (buff_write_idx + 1) % CMD_BUFFER_DIM; /* Atualiza o indice de escrita */
    mutex_unlock_semExMut(); /* Desbloqueia o trinco */
    sem_post(&posicoesOcupadas); /* Avisa que existem posicoes ocupadas */

} /* Funcao que coloca no buffer */

void *trata_tarefas(void* i) {

    while (emAtividade) {

        sem_wait(&posicoesOcupadas); /* Espera por uma posicao ocupada */
        mutex_lock_semExMut(); /* Bloqueia o trinco para impedir outra leitura */
        comando_t info = cmd_buffer[buff_read_idx]; /* Retira uma estrutura do buffer */
        buff_read_idx = (buff_read_idx + 1) % CMD_BUFFER_DIM; /* Atualiza o indice de leitura */
        mutex_unlock_semExMut(); /* Desbloqueia o trinco */
        sem_post(&posicoesVazias); /* Avisa que existem posicoes vazias */

        if (info.operacao != SAIR){

            sprintf(pipeID, "i-banco-tunnel-%d", info.PID); /* Criacao do nome do pipe conforme o pid */

            if ((fifo2 = open(pipeID, O_WRONLY)) < 0) {
                perror("Opening Tunnel Error");
            } /* Abertura do pipe de comunicacao com i-banco-terminal */

            if (info.operacao == CREDITAR) {
                mutex_lock_trincoContas(info.idConta - 1);

                creditar (info.idConta, info.valor);

                sprintf(str2, "%s(%d, %d): OK\n\n", COMANDO_CREDITAR, info.idConta, info.valor);
                sprintf(str, "%lu: %s %d %d\n", pthread_self(), COMANDO_CREDITAR, info.idConta, info.valor);

                mutex_unlock_trincoContas(info.idConta - 1);
            } /* Comando Creditar */

            else if (info.operacao == TRANSFERIR) {
                if (info.idConta > info.idDestino) {
                    mutex_lock_trincoContas(info.idDestino - 1); /* Bloqueia o trinco associado a conta idConta*/
                    mutex_lock_trincoContas(info.idConta - 1); /* Bloqueia o trinco associado a conta idDestino*/
                }/* Verificacao para impedir interblocagem */

                else if (info.idDestino > info.idConta) {
                    mutex_lock_trincoContas(info.idConta - 1); /* Bloqueia o trinco associado a conta idConta*/
                    mutex_lock_trincoContas(info.idDestino - 1); /* Bloqueia o trinco associado a conta idDestino*/
                }/* Verificacao para impedir interblocagem */

                else if (info.idConta == info.idDestino) {
                    sprintf(str2, "Erro ao %s %d da conta %d para a conta %d.\n\n", COMANDO_TRANSFERIR, info.valor, info.idConta, info.idDestino);
                    continue;
                    } /* As contas nao podem ser iguais */

                if (debitar (info.idConta, info.valor) < 0) {
                    sprintf(str2, "Erro ao %s %d da conta %d para a conta %d.\n\n", COMANDO_TRANSFERIR, info.valor, info.idConta, info.idDestino);
                } /* Nao tem saldo suficiente para fazer debito */
                else {
                    creditar (info.idDestino, info.valor);
                    sprintf(str2, "%s(%d, %d, %d): OK\n\n", COMANDO_TRANSFERIR, info.idConta, info.idDestino, info.valor);
                }

                sprintf(str, "%lu: %s %d %d %d\n", pthread_self(), COMANDO_TRANSFERIR, info.idConta, info.idDestino, info.valor);

                mutex_unlock_trincoContas(info.idConta - 1); /* Desbloqueia o trinco associado a conta idConta*/
                mutex_unlock_trincoContas(info.idDestino - 1); /* Desbloqueia o trinco associado a conta idDestino*/
            } /* Comando Transferir */

            else if (info.operacao == DEBITAR) {
                mutex_lock_trincoContas(info.idConta - 1); /* Bloqueia o trinco associado a conta idConta*/
                if (debitar (info.idConta, info.valor) < 0) {
                    sprintf(str2, "%s(%d, %d): Erro\n\n", COMANDO_DEBITAR, info.idConta, info.valor);
                } /* Nao tem saldo suficiente para fazer debito */
                else {
                    sprintf(str2, "%s(%d, %d): OK\n\n", COMANDO_DEBITAR, info.idConta, info.valor);
                } /* O debito e possivel */

                sprintf(str, "%lu: %s %d %d\n", pthread_self(), COMANDO_DEBITAR, info.idConta, info.valor);

                mutex_unlock_trincoContas(info.idConta - 1); /* Desbloqueia o trinco associado a conta idConta*/
            } /* Comando Debitar */

            else if (info.operacao == LER_SALDO) {
                mutex_lock_trincoContas(info.idConta - 1); /* Bloqueia o trinco associado a conta idConta*/

                sprintf(str2, "%s(%d): O saldo da conta é %d.\n\n", COMANDO_LER_SALDO, info.idConta, lerSaldo(info.idConta));
                sprintf(str, "%lu: %s %d\n", pthread_self(), COMANDO_LER_SALDO, info.idConta);

                mutex_unlock_trincoContas(info.idConta - 1); /* Desbloqueia o trinco associado a conta idConta*/
            } /* Comando lerSaldo */

            write(fid, str, 64); /* Escreve no ficheiro "log.txt" */
            write(fifo2, str2, 64); /* Escreve no i-banco-terminal atraves do pipe */
            close(fifo2); /* Fecha o pipe */

            }

            else {
                mutex_unlock_semExMut();
        	    printf("** Tarefa trabalhadora terminou. **\n");
        	    pthread_exit(NULL);
            } /* Comando Sair */

        mutex_lock_trincoOperacoes(); /* Bloqueia o trinco associado a manipulacao da variavel contadorOperacoesAtivas*/
        contadorOperacoesAtivas --; /* Atualiza o contador, visto que uma operacao terminou */
        if (contadorOperacoesAtivas == 0) {
            pthread_cond_signal(&condition);
        } /* Se a variavel contadorOperacoesAtivas for zero, e enviado um signal para o pthread_cond_wait que permite a
        a realizacao do comando Simular */
        mutex_unlock_trincoOperacoes(); /* Desbloqueia o trinco associado a manipulacao da variavel contadorOperacoesAtivas*/

    }

    pthread_exit(EXIT_SUCCESS); /* Sai da tarefa */
} /* Funcao trata tarefas */

int main (int argc, char** argv) {

    int  pid_index = 0; /* Indica o numero de processos filho criados */
    int  vec_pid[NUM_PROC_FILHO]; /* Vetor que contem o pid de todos os processos filho */

    /* Criacao de elementos de sincronizacao */

    sem_init(&posicoesOcupadas, 0, 0); /* Inicia o semaforo das posicoes ocupadas */
    sem_init(&posicoesVazias, 0, CMD_BUFFER_DIM); /* Inicia o semaforo das posicoes vazias */

    if (pthread_mutex_init(&trincoOperacoes, NULL) != 0) {
        perror("Erro na criacao do mutex.\n");
        exit(EXIT_FAILURE);
    } /* Inicializa o mutex e verifica se ocorreu erros */

    if (pthread_mutex_init(&semExMut, NULL) != 0) {
        perror("Erro na criacao do mutex.\n");
        exit(EXIT_FAILURE);
    } /* Inicializa o mutex e verifica se ocorreu erros */

    for (int i = 0; i < NUM_CONTAS; i++) {
        if(pthread_mutex_init(&trincoContas[i], NULL) != 0) {
            perror("Erro na criacao do mutex.\n");
            exit(EXIT_FAILURE);
        } /* Caso ocorra algum erro */
    } /* Inicializa os trincos das contas */

    if (pthread_cond_init(&condition, NULL) != 0) {
        perror("Erro na criacao do mutex.\n");
        exit(EXIT_FAILURE);
    } /* Inicializa a variavel de condicao referenciada por condition e verifica se ocorreu erros */

    /* Criacao das Tarefas */

    for (int i = 0; i < NUM_TRABALHADORAS; i++) {
        if (pthread_create(&tid[i], NULL, trata_tarefas, NULL)) {
            perror("Erro na criacao da thread.\n");
            exit(EXIT_FAILURE);
        }
    } /* Criacao das tarefas */

    /* Inicializa o signal */

    if (signal(SIGUSR1, muda_SIG) == SIG_ERR) {
        perror("Erro ao definir signal.");
    } /* Associa um signal a rotina que o trata */

    /* Cria ficheiro "log.txt" */

    if ((fid = open("log.txt", O_CREAT|O_TRUNC|O_RDWR, 0666)) == 0) {
        perror("Erro na criacao do ficheiro.\n");
        exit(-1);
    } /* Verificar que fechamos o ficheiro IMPORTANTE */

    /* Inicia Banco */

    printf("Bem-vinda/o ao i-banco\n\n");

    inicializarContas();

    /* Cria o i-banco-pipe */

    mkfifo("i-banco-pipe", 0666);
    int fifo = open("i-banco-pipe",O_RDONLY);

    while (1) {

        comando_t buf;
        read(fifo, &buf, sizeof(comando_t));

        if (buf.operacao == SAIR) {

            for (int i = 0; i < NUM_TRABALHADORAS; i++) {
                colocaBuffer(buf); /* Coloca a estrutura criada no buffer */
            } /* Coloca o comando sair no buffer para as NUM_TRABALHADORAS tarefas o receberem */

            for (int i = 0; i < NUM_TRABALHADORAS; i++) {
                if ((pthread_join(tid[i], NULL) != 0)) {
                    perror("Erro ao esperar pela thread");
                } /* Caso ocorra algum erro */
            } /* Espera pelo fim das tarefas ativas */

            printf("i-banco vai terminar.\n--\n");

            if (buf.flag_sair_agora == 1) {
                for (int i = 0; i < pid_index; i++) {
                    kill(vec_pid[i], SIGUSR1);
                } /* Envia o signal a todos os processos ativos */
            } /* O comando dado foi o "sair agora" */

            for (int i = 0; i < pid_index; i++) {
                int estadoProcesso; /* Guarda o estado de como o processo terminou */
                waitpid(vec_pid[i], &estadoProcesso, 0); /* Aguarda pelo termino de todos os processos filhos */

                if (WIFEXITED(estadoProcesso)) {
                    printf("FILHO TERMINADO (PID=%d; terminou normalmente)\n", vec_pid[i]);
                } /* Caso o processo filho termine sem erros */
                else {
                    printf("FILHO TERMINADO (PID=%d; terminou abruptamente)\n", vec_pid[i]);
                } /* Caso ocorra um erro no termino do processo filho */
            } /* Percorre todos os processos criados */

            for (int i = 1; i <= NUM_TRABALHADORAS; i++) {
                printf("Info: Terminada tarefa(%d)\n", i);
            } /* Notifica que as tarefas foram terminadas */

            /* Destroi elementos de sincronizacao */
            for (int i = 0; i < NUM_CONTAS; i++) {
                pthread_mutex_destroy(&trincoContas[i]);
            }

            pthread_mutex_destroy(&trincoOperacoes);
            pthread_mutex_destroy(&semExMut);

            sem_destroy(&posicoesVazias);
            sem_destroy(&posicoesOcupadas);

            pthread_cond_destroy(&condition);

            close(fifo); /* Fecha o pipe */
            close(fid);  /* Fecha o "log.txt" */
            unlink("i-banco-pipe"); /* Remove o pipe */

            printf("--\ni-banco terminou.\n");

            exit(EXIT_SUCCESS);
        } /* EOF (end of file) do stdin ou comando "sair" */

        else if (buf.operacao == DEBITAR) {

            colocaBuffer(buf);

        } /* Comando "Debitar" */

        else if (buf.operacao == CREDITAR) {

            colocaBuffer(buf);

        } /* Comando "Creditar" */

        else if (buf.operacao == TRANSFERIR) {

            colocaBuffer(buf);

        } /* Comando "Transferir" */

        else if (buf.operacao == LER_SALDO) {

            colocaBuffer(buf);

        } /* Comando "Ler Saldo" */

        else if (buf.operacao == SIMULAR) {

            if (pid_index >= NUM_PROC_FILHO) {
                printf("%s: Atingido o numero maximo de processos filho a criar.\n", COMANDO_SIMULAR);
                continue;
            } /* Verifica se a quantidade maxima foi atingida */

            mutex_lock_trincoOperacoes();/* Bloqueia o trinco associado a manipulacao da variavel contadorOperacoesAtivas*/
            while (contadorOperacoesAtivas != 0){
                pthread_cond_wait(&condition, &trincoOperacoes);
            } /* Enquanto a varivel contadorOperacoesAtivas for zero, o simular fica bloqueado ate receber um signal de que
            e possivel realizar-se este comando*/
            mutex_unlock_trincoOperacoes();/* Desbloqueia o trinco associado a manipulacao da variavel contadorOperacoesAtivas*/

            int numAnos = buf.numAnos;
            int pid = fork(); /* Criacao do processo filho */

            if (pid == 0) {

                sprintf(str, "i-banco-sim-%d.txt", getpid());
                fid = open(str, O_CREAT | O_RDWR, 0666); /* Cria o ficheiro com o output das simulacoes */
                dup2(fid, 1); /* Coloca o ficheiro criado como destino das impressoes */

                simular(numAnos);

                close(fid); /* Fecha o ficheiro criado */
                exit(EXIT_SUCCESS);
            } /* Executa o codigo do processo filho */
            else if (pid > 0) {
                vec_pid[pid_index] = pid;
                pid_index++;
                printf("%s(%d): Simulacao iniciada em background.\n\n", COMANDO_SIMULAR, numAnos);
                continue;
            } /* Executa o codigo do processo pai */
            else if (pid < 0) {
                perror("Falhou a criacao do novo processo, tente de novo");
                exit(EXIT_FAILURE);
            }
        } /* Executa o comando com sucesso */
     /* Comando "Simular" */

        else {
            printf("Comando desconhecido. Tente de novo.\n");
        } /* Comando nao existente ou com erros de escrita */

    } /* Termina o ciclo while que mantem o programa a correr */
} /* Fim da Tarefa Inicial */
