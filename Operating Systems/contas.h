/*
// Operações sobre contas, versao 1
// Sistemas Operativos, DEI/IST/ULisboa 2016-17
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#ifndef CONTAS_H
#define CONTAS_H

#define max(a,b) ((a) > (b) ? (a) : (b))
#define NUM_CONTAS 10
#define TAXAJURO 0.1
#define CUSTOMANUTENCAO 1

#define ATRASO 1
#define atrasar() sleep(ATRASO)

void inicializarContas();
int contaExiste(int idConta);
int debitar(int idConta, int valor);
int creditar(int idConta, int valor);
int lerSaldo(int idConta);
void simular(int numAnos);
void printSaldos();
void muda_SIG(int signum);
void muda_SIG2(int signum);

#endif
