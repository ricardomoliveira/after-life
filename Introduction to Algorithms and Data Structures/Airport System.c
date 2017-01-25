//IST - TAGUSPARK
//PROJETO 1 IAED

//Ricardo Oliveira, 84759
//Ricardo Martins, 84761

////////////////////////////////////////////////////////////////////////////////
//                               BIBLIOTECAS                                  //
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////
//                               ESTRUTURAS                                   //
////////////////////////////////////////////////////////////////////////////////

typedef struct aeroporto {
	char id[4];
	int  capacidade;
	int  estado;

} AEROPORTO; // Definicao da estrutura que define os detalhes de cada aeroporto

////////////////////////////////////////////////////////////////////////////////
//                               VARIAVEIS                                    //
////////////////////////////////////////////////////////////////////////////////

#define MAX 1000            // Maximo de aeroportos suportados

AEROPORTO aero[MAX];        // Lista de estruturas do tipo aeroporto
int       matriz[MAX][MAX]; // Matriz representativa das ligacoes aereas
int       N_AEROPORTOS = 0; // Quantidade de aeroportos criados

////////////////////////////////////////////////////////////////////////////////
//                               PROTOTIPOS                                   //
////////////////////////////////////////////////////////////////////////////////

void adiciona_aero(void); // Adiciona um novo aeroporto
void encerra_aero(void);  // Encerra um aeroporto existente e termina conexoes
void adiciona_voo_ida_volta(void); //Adiciona voo ida e volta de id_partida para 1d_chegada
void adiciona_rota(void); // Adiciona voo de ida de id_partida para id_chegada
void altera_capacidade(void); // Altera a capacidade de um aeroporto existente
void listagem_aero(void); // Emite lista de aeroportos e voos totais
void numero_voos(void);   //
void reabre_aero(void);   // Abre um aeroporto existente que tenha sido fechado
void aero_mais_voos(void); //  Indica o aeroporto com maior numero total de voos
void aero_mais_conectado(void); // Indica o aeroporto com mais ligacoes aereas
void remove_voo(void); // Remove voo de ida de id_partida para id_chegada
void remove_voo_ida_volta(void); // Remove voo ida e volta de id_partida para id_chegada
void popularidade_voo(void); // Indica o par de aeroportos com maior numero de voos a partir de id_partida para id_chegada
void saida(void); // Sai e emite a lista de numero de voos e aeroportos ativos

int numero_voos_aeroporto_partida(int index); // Indica o numero de voos de partida de um aeroporto
int numero_voos_aeroporto_chegada(int index); // Indica o numero de voos de chegada de um aeroporto
int get_index(char id[]); // Procura um id de um aeroporto na lista e retorna a sua posicao
int conexoes(int index);  // Indica as ligacoes aereas de um aeroporto

////////////////////////////////////////////////////////////////////////////////
//			                             CODIGO	    		                          //
////////////////////////////////////////////////////////////////////////////////

int main() {

	char cmd;
	while (1) {
		cmd = getchar(); // Recebe o comando do utilizador
		switch (cmd) {
			case 'A': adiciona_aero(); break;
			case 'C': encerra_aero(); break;
			case 'F': adiciona_voo_ida_volta(); break;
			case 'G': adiciona_rota(); break;
			case 'I': altera_capacidade(); break;
			case 'L': listagem_aero(); break;
			case 'N': numero_voos(); break;
			case 'O': reabre_aero(); break;
			case 'P': aero_mais_voos(); break;
			case 'Q': aero_mais_conectado(); break;
			case 'R': remove_voo(); break;
			case 'S': remove_voo_ida_volta(); break;
			case 'V': popularidade_voo(); break;
			case 'X':
					  saida();
				      return EXIT_SUCCESS;
				      break;
			default: printf("ERRO: Comando Invalido\n");
		}
		getchar();
	}
	return EXIT_FAILURE;
}

////////////////////////////////////////////////////////////////////////////////
//			                           COMANDOS			                              //
////////////////////////////////////////////////////////////////////////////////

/*
	adiciona_aero :
		cria um aeroporto no vetor de estruturas
		aero no indice N_AEROPORTOS com id e
		capacidade igual ao input do utilizador
		e estado igual a 1.
*/

void adiciona_aero(void)
{

	char id[4];
	int capacidade, index;

	scanf(" %s %d", id, &capacidade);
	index = N_AEROPORTOS; // Indica a posicao do novo aeroporto no vetor de estruturas

	if (capacidade > 0) {
		strcpy(aero[index].id, strcat(id, "\0")); // Copia o id do aeroporto para a respetiva posicao no vetor
		aero[index].capacidade = capacidade;
		aero[index].estado = 1; // Declara o aeroporto como aberto
		N_AEROPORTOS++; // Atualiza o indice para a posicao do proximo aeroporto a ser aberto
	}
}

/*
	encerra_aero :
		encerra o aeroporto cujo o id e igual
		ao do input do utilizador, colocando
		o seu estado a -1 no vetor de estruturas
		aero e na matriz[MAX][MAX] poe todos os
		voos deste aeroporto a 0.
		Caso nao existe nenhuma estrutura com
		o id igual ao do input do utilizador,
		a funcao imprime "*Aeroporto id
		inexistente".
*/

void encerra_aero(void)
{

	char id[4];
	int index, i;

	scanf(" %s", id);

	index = get_index(id); // Retorna a posicao do aeroporto no vetor de estruturas

	if (index == -1) // Se nao existir nenhum id correpondente no vetor

		printf("*Aeroporto %s inexistente\n", id);

	else {

		aero[index].estado = 0; // Declara o aeroporto como fechado

		for (i = 0; i < N_AEROPORTOS; i++) {
			matriz[index][i] = 0; // Anula os voos de partida do aeroporto
			matriz[i][index] = 0; // Anula os voos de chegada do aeroporto
		}
	}
}

/*
	adiciona_voo_ida_volta :
		adiciona um voo em matriz[id_partida][id_chegada] e outro em
		matriz[id_chegada][id_partida], sendo que id_partida e id_chegada correspondem
		ao input do utilizador.
		Caso um dos id's nao exista na matriz de estruturas
		ou um dos estados dos aeroportos seja 0 ou o novo
		numero de voos de um dos aeroportos seja maior que
		a sua capacidade a funcao imprime "*Impossivel adicionar voo RT id_partida id_chegada".
*/

void adiciona_voo_ida_volta(void)
{

	char id_partida[4], id_chegada[4];
	int  index_partida, index_chegada;

	scanf(" %s %s", id_partida, id_chegada);

	index_partida = get_index(id_partida); // Indica a posicao do aeroporto de partida no vetor de estruturas
	index_chegada = get_index(id_chegada); // Indica a posicao do aeroporto de chegada no vetor de estruturas

	if (index_chegada == -1 || index_partida == -1 || aero[index_chegada].estado == 0 || aero[index_partida].estado == 0 ||
  numero_voos_aeroporto_chegada(index_chegada) + numero_voos_aeroporto_partida(index_chegada) + 2 > aero[index_chegada].capacidade ||
  numero_voos_aeroporto_chegada(index_partida) + numero_voos_aeroporto_partida(index_partida) + 2 > aero[index_partida].capacidade) {
		printf("*Impossivel adicionar voo RT %s %s\n", id_partida, id_chegada);
	}
	else {
		matriz[index_partida][index_chegada] += 1; // Atualiza a quantidade de voos com partida em id_partida e chegada em id_chegada [Adiciona]
		matriz[index_chegada][index_partida] += 1; // Atualiza a quantidade de voos com partida em id_chegada e chegada em id_partida [Adiciona]
	}
}

/*
	adiciona_rota :
		adiciona um voo em matriz[id_partida][id_chegada], sendo que id_partida
		e id_chegada correspondem ao input do utilizador.
		Caso um dos id's nao exista na matriz de estruturas
		ou um dos estados dos aeroportos seja 0 ou o novo
		numero de voos de um dos aeroportos seja maior que
		a sua capacidade a funcao imprime "*Impossivel adicionar voo id_partida id_chegada".
*/

void adiciona_rota(void)
{

	char id_partida[4], id_chegada[4];
	int index_partida, index_chegada;

	scanf(" %s %s", id_partida, id_chegada);

	index_partida = get_index(id_partida); // Indica a posicao do aeroporto de partida no vetor de estruturas
	index_chegada = get_index(id_chegada); // Indica a posicao do aeroporto de chegada no vetor de estruturas

	if (index_chegada == -1 || index_partida == -1 || aero[index_chegada].estado == 0 || aero[index_partida].estado == 0 ||
	numero_voos_aeroporto_partida(index_partida) + 1 + numero_voos_aeroporto_chegada(index_partida) > aero[index_partida].capacidade ||
	numero_voos_aeroporto_chegada(index_chegada) + numero_voos_aeroporto_partida(index_chegada) + 1 > aero[index_chegada].capacidade)
		printf("*Impossivel adicionar voo %s %s\n", id_partida, id_chegada);
	else
		matriz[index_partida][index_chegada] += 1;  // Atualiza a quantidade de voos com partida em id_partida e chegada em id_chegada [Adiciona]
}

/*
	altera_capacidade :
		ao valor inicial da capacidade(antes de entrar neste comando),
		soma ou subtrai o valor de um inteiro, que corresponde ao segundo
		input do utilizador, no aeroporto com id igual ao primeiro
		input do utilizador.
		Caso o id do input nao exista na matriz de estruturas
		ou o estado do aeroporto seja 0 ou a nova capacidade
		do aeroporto seja menor que o numero de voos do proprio aeroporto
		a funcao imprime "*Capacidade de id inalterada".

*/

void altera_capacidade(void)
{

	char id[4];
	int index, nova_capacidade;

	scanf(" %s %d", id, &nova_capacidade);

	index = get_index(id); // Indica a posicao do aeroporto no vetor de estruturas

	if (index == -1 || aero[index].estado == 0 ||
	aero[index].capacidade + nova_capacidade < numero_voos_aeroporto_partida(index) + numero_voos_aeroporto_chegada(index))
		printf("*Capacidade de %s inalterada\n", id);
	else
		aero[index].capacidade += nova_capacidade; // Atualiza a capacidade do aeroporto na estrutura respetiva
}

/*
	numero_voos :
		calcula o numero de voos que partem de id_partida e chegam a id_chegada(voos de ida)
		e os voos que partem de id_chegada e chegam a id_partida(voos de chegada) em que os id's
		correspondem ao input do utilizador e imprime "Voos entre cidades
		id_partida:id_chegada:voos de ida:voos de chegada
		Caso um dos id's nao exista no vetor de estruturas aero a funcao
		imprime "*Aeroporto id inexistente".
*/

void numero_voos(void)
{

	char id_partida[4], id_chegada[4];
	int index_partida, index_chegada, voos_partida, voos_chegada;

	scanf(" %s %s", id_partida, id_chegada);

	index_partida = get_index(id_partida); // Indica a posicao do aeroporto de partida no vetor de estruturas
	index_chegada = get_index(id_chegada); // Indica a posicao do aeroporto de chegada no vetor de estruturas

	if (index_partida == -1) { // Se o aeroporto de partida nao existe
		printf("*Aeroporto %s inexistente\n", id_partida);
	}
	else if (index_chegada == -1) { // Se o aeroporto de chegada nao existe
		printf("*Aeroporto %s inexistente\n", id_chegada);
	}
	else if (index_partida == -1 && index_chegada == -1) { // Se nenhum dos dois existe
		printf("*Aeroporto %s inexistente /n *Aeroporto %s inexistente\n", id_partida, id_chegada);
	}
	else {
		voos_partida = matriz[index_partida][index_chegada]; // Retorna o numero de voos com partida em id_partida e chegada em id_chegada
		voos_chegada = matriz[index_chegada][index_partida]; // Retorna o numero de voos com partida em id_chegada e chegada em id_partida

		printf("Voos entre cidades %s:%s:%d:%d\n", id_partida, id_chegada, voos_partida, voos_chegada);
	}
}

/*
	reabre_aero :
		reabre o aeroporto cujo o id e igual ao do input
		do utilizador, colocando o seu estado a 1 no
		vetor de estruturas aero.
		Caso nao existe nenhuma estrutura com o id igual
		ao do input do utilizador, a funcao imprime
		"*Aeroporto id inexistente".
*/

void reabre_aero(void)
{
	int index;
	char id[4];

	scanf(" %s", id);

	index = get_index(id);  // Indica a posicao do aeroporto no vetor de estruturas

	if (index == -1) // Se o aeroporto nao existe
		printf("*Aeroporto %s inexistente\n", id);
	else
		aero[index].estado = 1; // Altera o estado do aeroporto para aberto
}

/*
	aero_mais_voos :
		calcula o aeroporto com mais voos na matriz[MAX][MAX]
		e imprime "Aeroporto com mais rotas id:voos de partida:voos de chegada" em que
		id corresponde ao aeroporto com mais voos, voos de partida representa os voos
		que partem do aeroporto id e voos de chegada representa os voos que chegam
		ao aeroporto id.
*/

void aero_mais_voos(void)
{
	int i, variavel, max_index = 0, max = numero_voos_aeroporto_partida(0) + numero_voos_aeroporto_chegada(0);

	for (i = 1; i < N_AEROPORTOS; i++) // Percorre a lista de aeroportos existentes
	{
		variavel = numero_voos_aeroporto_partida(i) + numero_voos_aeroporto_chegada(i); // Atribui o total de voos de um aeroporto
		if (variavel > max)
		{
			max = variavel; // Total de voos do aeroporto com mais voos
			max_index = i;  // Atualiza o indice para o do aeroporto com mais voos
		}
	}
	printf("Aeroporto com mais rotas %s:%d:%d\n", aero[max_index].id, numero_voos_aeroporto_partida(max_index), numero_voos_aeroporto_chegada(max_index));
}

/*
	aero_mais_conectado :
		calcula o aeroporto mais conectado na matriz[MAX][MAX]
		e imprime "Aeroporto com mais ligacoes id:conexoes" em que
		id corresponde ao aeroporto com mais conexoes e conexoes ao
		numero de conexoes do aeroporto id.
*/

void aero_mais_conectado(void)
{
	int i, max = 0;

	for (i = 0; i < N_AEROPORTOS; i++) // Percorre a lista de aeroportos existentes
	{
		if (conexoes(i) > conexoes(max))
			max = i; // Atualiza o indice para o do aeroporto com mais conexoes
	}
	printf("Aeroporto com mais ligacoes %s:%d\n", aero[max].id, conexoes(max));
}

/*
	remove_voo :
		remove um voo com partida em id_partida e chegada em id_chegada
		na matriz[MAX][MAX], sendo que id_partida e id_chegada correspondem
		ao input do utilizador.
		Caso um dos id's nao exista no vetor de estruturas aero
		ou um dos estados dos aeroportos seja 0 ou o numero
		de voos de com partida em id_partida e chegada em id_chegada seja
		0 a funcao imprime "*Impossivel adicionar voo id_partida id_chegada".
*/

void remove_voo(void)
{
	char id_partida[4], id_chegada[4];
	int index_partida, index_chegada;

	scanf(" %s %s", id_partida, id_chegada);

	index_partida = get_index(id_partida); // Indica a posicao do aeroporto de partida no vetor de estruturas
	index_chegada = get_index(id_chegada); // Indica a posicao do aeroporto de chegada no vetor de estruturas

	if (index_chegada == -1 || index_partida == -1 || aero[index_chegada].estado == 0 || aero[index_partida].estado == 0 ||
	matriz[index_partida][index_chegada] == 0)
		printf("*Impossivel remover voo %s %s\n", id_partida, id_chegada);
	else
		matriz[index_partida][index_chegada] -= 1; // Atualiza a quantidade de voos com partida em id_partida e chegada em id_chegada [Remove]
}

/*
	remove_voo_ida_volta :
		remove um voo com partida em id_partida e chegada em id_chegada e um
		voo com partida em id_chegada e chegada em id_partida na matriz[MAX][MAX],
		sendo que id_partida e id_chegada correspondem ao input do utilizador.
		Caso um dos id's nao exista no vetor de estruturas aero
		ou um dos estados dos aeroportos seja 0 ou o numero de voos
		de com partida em id_partida e chegada em id_chegada seja 0 a funcao
		imprime "*Impossivel adicionar voo id_partida id_chegada".
*/

void remove_voo_ida_volta(void)
{
	char id_partida[4], id_chegada[4];
	int index_partida, index_chegada;

	scanf(" %s %s", id_partida, id_chegada);

	index_partida = get_index(id_partida); // Indica a posicao do aeroporto de partida no vetor de estruturas
	index_chegada = get_index(id_chegada); // Indica a posicao do aeroporto de chegada no vetor de estruturas

	if (index_chegada == -1 || index_partida == -1 || aero[index_chegada].estado == 0 || aero[index_partida].estado == 0 ||
	matriz[index_partida][index_chegada] == 0 || matriz[index_chegada][index_partida] == 0)
		printf("*Impossivel remover voo RT %s %s\n", id_partida, id_chegada);
	else
	{
		matriz[index_partida][index_chegada] -= 1; // Atualiza a quantidade de voos com partida em id_partida e chegada em id_chegada [Remove]
		matriz[index_chegada][index_partida] -= 1; // Atualiza a quantidade de voos com partida em id_chegada e chegada em id_partida [Remove]
	}
}

/*
	popularidade_voo :
		calcula o voo mais popular na matriz[MAX][MAX] e
		imprime "Voo mais popular id_partida:id_chegada:max" em que os
		id's correspondem a dois aeroportos e max ao numero
		de voos que partem em id_partida e chegam a id_chegada.
*/

void popularidade_voo(void)
{
	int i, j, max_voos = 0, aero_partidas = 0, aero_chegadas = 0;

	for (i = 0; i < N_AEROPORTOS; i++)
	{
		for (j = 0; j < N_AEROPORTOS; j++)
		{
			if (matriz[i][j] > max_voos) // Percorre todas as posicoes da matriz cujas entradas sao os voos
			{
				max_voos = matriz[i][j];
				aero_partidas = i; // Indica o indice do aeroporto de partida respetivo ao voo mais popular
				aero_chegadas = j; // Indica o indice do aeroporto de chegada respetivo ao voo mais popular
			}
		}
	}
	printf("Voo mais popular %s:%s:%d\n", aero[aero_partidas].id, aero[aero_chegadas].id, max_voos);
}

/*
	saida :
		Acede ao numero de aeroportos que foram introduzidos pelo utilizador (n_aero)
		no vetor de estruturas aero e o numero de voos total
		que existem na matriz[MAX][MAX](n_voos) e imprime "n_voos:n_aero"
*/

void saida(void)
{
	int i, j, numero_voos = 0;

	for (i = 0; i < N_AEROPORTOS; i++)
	{
		for (j = 0; j < N_AEROPORTOS; j++)
		{
			numero_voos += matriz[i][j]; // Atualiza o total de voos existentes
		}
	}
	printf("%d:%d\n", numero_voos, N_AEROPORTOS);
}

/*
	listagem_aero :

		0 - a funcao imprime "aero_id:aero_capacidade:voos_partida:voos_chegada"
		para todos os aeroportos introduzidos pelo utilizador em que aero_id
		corresponde ao nome do aeroporto, aero_capacidade à sua capacidade,
		voos_partida ao numero de voos que partem do aeroporto e voos_partida ao
		numero de voos que chegam ao aeroporto.

		1 - a funcao ordena os aeroportos introduzidos pelo utilizador por ordem
		lexicografica no clone do vetor de estruturas, criado inicialmente, e imprime
		"aero_id:aero_capacidade:voos_partida:voos_chegada" em que aero_id
		corresponde ao nome do aeroporto, aero_capacidade à sua capacidade,
		voos_partida ao numero de voos que partem do aeroporto e voos_partida ao
		numero de voos que chegam ao aeroporto.

		2 - a funcao imprime um histograma d(k) sob a forma "k:d(k)" em que d()
		corresponde ao numero de aeroportos atualmente com exatamente k voos
		(total de partidas e chegadas).
*/

void listagem_aero(void)
{
	int variavel, contador, i, j, nvoos[N_AEROPORTOS], k, index;
	char temp[4];
	AEROPORTO clone[MAX];

	scanf(" %d", &variavel);

	switch (variavel)
	{
	case 0:

		for (i = 0; i < N_AEROPORTOS; i++)
			printf("%s:%d:%d:%d\n", aero[i].id, aero[i].capacidade, numero_voos_aeroporto_partida(i), numero_voos_aeroporto_chegada(i));

	break;

	case 1:

		// Processo de clonagem do vetor de estruturas
		for (i = 0; i < MAX; i++)
		{
			clone[i] = aero[i]; // Copia o vetor de estruturas original
			strcpy(clone[i].id, aero[i].id); // Copia os id das estruturas do vetor original
			clone[i].capacidade = aero[i].capacidade; // Copia a capacidade das estruturas do vetor original
		}

		// Processo de ordenacao dos ids dos aeroportos no vetor de estruturas clonado
		for(i=1; i < N_AEROPORTOS; i++)
		{
			for(j=0; j < N_AEROPORTOS - i; j++)
			{
				if(strcmp(clone[j].id, clone[j+1].id) > 0) // Compara os id de posicoes consecutivas
				{
  					strcpy(temp, clone[j].id); // Coloca o id com a string maior numa variavel temporaria
  					strcpy(clone[j].id, clone[j+1].id); // Coloca o id com a string menor na posicao inferior
  					strcpy(clone[j+1].id, temp); // Coloca o id na variavel temporaria de volta a posicao superior
				}
			}
		}

		// Processo de impressao dos ids ja ordenados com os voos e capacidades correspondentes
		for (i = 0; i < N_AEROPORTOS; i++)
		{
			index = get_index(clone[i].id);
			printf("%s:%d:%d:%d\n", clone[i].id, aero[index].capacidade, numero_voos_aeroporto_partida(index), numero_voos_aeroporto_chegada(index));
		};

		break;

	case 2:

	// Cria um vetor com a quantidade de voos respetivos aos varios aeroportos
	for (i = 0; i < N_AEROPORTOS; i++)
		nvoos[i] = numero_voos_aeroporto_partida(i) + numero_voos_aeroporto_chegada(i);

	// Processo de contagem da quantidade de aeroportos que apresentam uma certa quantidade voos
	for (j = 0; j <= MAX; j++)
	{
		for (k = 0, contador = 0; k < N_AEROPORTOS; k++)
		{
			if (nvoos[k] == j) // Se encontrar no vetor um numero igual de voos
				contador += 1;   // Atualiza a quantidade de aeroportos com o numero respetivo de voos
		}
		if (contador != 0)   // Imprime apenas se o numero de aeroportos for diferente de zero
			printf("%d:%d\n", j, contador);
	}
	};
}

////////////////////////////////////////////////////////////////////////////////
//			                      FUNCOES AUXILIARES			                        //
////////////////////////////////////////////////////////////////////////////////

/*
	get_index :
		devolve o indice do vector de aeroportos cujo identificador
		e passado como parametro
	parametros :
		id - identificador de aeroporto
	retorna  :
		um inteiro que representa um indice do vector de aeroportos
		caso não exista o identificador devolve -1
	*/

int get_index(char id[])
{
	int i;

	for (i = 0; i < N_AEROPORTOS; i++)
	{
		if (strcmp(id, aero[i].id) == 0)
			return i;
	}
	return -1;
}

/*
	numero_voos_aeroporto_partida :
		devolve o numero de voos que partem de um aeroporto
	parametros:
		indice do aeroportos
	retorna:
		numero de voos de partida
	*/

int numero_voos_aeroporto_partida(int index)
{
	int i, soma = 0;

	for (i = 0; i < N_AEROPORTOS; i++)
		soma += matriz[index][i];

	return soma;
}

/*
	numero_voos_aeroporto_chegada :
		devolve o numero de voos que chegam a um aeroporto
	parametros:
		indice do aeroporto
	retorna:
		numero de voos de chegada
*/

int numero_voos_aeroporto_chegada(int index)
{
	int i, soma = 0;

	for (i = 0; i < N_AEROPORTOS; i++)
		soma += matriz[i][index];

	return soma;
}

/*
	conexoes :
		devolve o numero de ligacoes de um aeroporto
	parametros:
		indice do aeroporto
	retorna:
		numero de ligacoes
*/

int conexoes(int index)
{
		int soma = 0, i;

		for (i = 0; i < N_AEROPORTOS; i++)
		{
			if (matriz[index][i] > 0 || matriz[i][index] > 0)
				soma++;
		}
		return soma;
}
