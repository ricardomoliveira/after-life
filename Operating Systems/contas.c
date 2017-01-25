#include "contas.h"

int SIG_recebido = 0;
int SIG_pipe = 0;

int contasSaldos[NUM_CONTAS];

int contaExiste(int idConta) {
  return (idConta > 0 && idConta <= NUM_CONTAS);
}

void inicializarContas() {
  int i;
  for (i=0; i<NUM_CONTAS; i++)
    contasSaldos[i] = 0;
}

int debitar(int idConta, int valor) {
  atrasar();
  if (!contaExiste(idConta))
    return -1;
  if (contasSaldos[idConta - 1] < valor)
    return -1;
  atrasar();
  contasSaldos[idConta - 1] -= valor;
  return 0;
}

int creditar(int idConta, int valor) {
  atrasar();
  if (!contaExiste(idConta))
    return -1;
  contasSaldos[idConta - 1] += valor;
  return 0;
}

int lerSaldo(int idConta) {
  atrasar();
  if (!contaExiste(idConta))
    return -1;
  return contasSaldos[idConta - 1];
}

void simular(int numAnos) {
	int id, anos;

    if (signal (SIGUSR1, muda_SIG) == SIG_ERR) {
        perror ("Erro ao instalar signal handler");
    }

	for (anos = 0; anos <= numAnos; anos++) {

        if (anos > 0) {
            for (id = 0; id <= NUM_CONTAS; id++) {
                contasSaldos[id] = max(lerSaldo(id + 1) * (1 + TAXAJURO) - CUSTOMANUTENCAO, 0);
            }
        }

        printf("\nSIMULACAO: Ano %d\n=================\n", anos);
		    printSaldos();

        if (SIG_recebido == 1) {
            printf("\nSimulacao terminada por signal\n");
            exit(EXIT_SUCCESS);
        } /* Verificacao se a flag SIG_recebido foi afetada pela interrupcao sair agora */
	}
} /* Simula o saldo de cada conta ao longo de "numAnos" anos tendo em conta
os juros "TAXAJURO" e os custos de manutencao de conta "CUSTOMANUTENCAO"
em cada ano. */

void printSaldos() {
	int id;
	for (id = 1; id <= NUM_CONTAS; id++) {
        printf("Conta %d, Saldo %d\n", id, lerSaldo(id));
	}
} /* Imprime no stdout o saldo das contas do vetor "contas" */

void muda_SIG(int signum) {
    SIG_recebido = 1;
} /* Rotina associada ao signal enviado pela interupcao "sair agora", que altera
a flag SIG_recebido para 1, afim de ser verificada mais a frente no comando simular */

void muda_SIG2(int signum) {
  if (signal(SIGPIPE, muda_SIG2) == SIG_ERR) {
      perror("Erro ao definir signal.");
  } /* Associa um signal a rotina que o trata */
  printf("Erro ao conectar ao i-banco\n");
} /* Rotina associada ao signal enviado pela interupcao "sair agora", que altera
a flag SIG_pipe para 1 */
