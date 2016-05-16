/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                #IST #TAGUSPARK #PROJETO2 #IAED                                /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////                                  Ricardo Oliveira, 84759                                      /////
/////                                  Ricardo Martins, 84761                                       /////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                       #Bibliotecas                                            /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                        #Constantes                                            /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#define NUMSEP 11
#define key(a) (a != NULL ? a->tag : "")
#define less(a,b) (strcmp(a,b)<0)
#define eq(a,b) (strcmp(a,b)==0)

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                         #Variaveis                                            /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

int Ntags = 0;
int Ntotal = 0;

Node Max_node = NULL;
Node root = NULL;

static const char separators[] = { ' ','\t',',',';','.','?','!','"','\n',':','\0' };

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                        #Estruturas                                            /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct hashtag {
    char* tag;
    int   count;
} *Hashtag;

typedef struct node {
    Hashtag hash;
    struct node* left;
    struct node* right;
} *Node;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                        #Prototipos                                            /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void split(char *line);
void processa_mensagem();
Hashtag newHash(char* nome);
Node newNode(Hashtag hash);
void actualizaMax(Node x);
Node insertR(Node h, Hashtag hash);
void STinsert(Node *head, Hashtag hash);
Node searchR(Node h, Hashtag hash);
void sortR(Node h, void(*visit)(Hashtag));
void STsort(Node head, void(*visit)(Hashtag));
Hashtag* Tree2Array(Node h, Hashtag*vec, int*i);
Hashtag* newVetor();
void printVetor(Hashtag* vec);
void merge(Hashtag* vec, int l, int m, int r);
void mergesort(Hashtag* vec, int l, int r);
void comando_l();
void lowercase(char * c);
void comando_m();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                          Codigo                                               /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    char cmd;
    while (1) {
        cmd = getchar(); // Recebe o comando do utilizador
        switch (cmd) {
        case 'a':
            processa_mensagem(); // Processa o texto introduzido pelo utilizador
            break;
        case 's':
            printf("%d %d\n", Ntags, Ntotal); // Imprime o numero de hashtags diferentes e o numero total de ocorrências
            break;
        case 'm':
            comando_m(); // Imprime a hashtag com maior numero de ocorrencias
            break;
        case 'l':
            comando_l(); // Imprime a lista de hashtags distintas introduzidas, pela ordem do numero de ocorrencias (ordem decrescente)
            break;
        case 'x':
            return EXIT_SUCCESS;
        }
    }
    return EXIT_FAILURE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                    Funcoes Principais                                         /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Comando 'a' - Recebe o texto introduzido pelo utilizador, recorrendo a funcao                       //
// fgets(output, lenght, input), posteriormente procurando a ocorrencia de hashtags e processando-as   //
// atraves da funcao split(input).                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void processa_mensagem()
{
    char texto[141];
    fgets(texto, 141, stdin);
    split(texto);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Comando 'm' - Imprime a hashtag com o maior numero de ocorrencia, requer a introducao de pelo menos //
// uma hashtag pela parte do utilizador.                                                               //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void comando_m()
{
    if (Max_node != NULL)
        printf("%s %d\n", key((Max_node->hash)), (Max_node->hash)->count);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Comando 'l' - Imprime a lista das distintas hashtags introduzidas pelo utilizador, pelo seu numero  //
// de ocorrencias de forma decrescente. Em caso de empate de ocorrencia, ordena as hashtags por        //
// ordem lexicografica.                                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void comando_l()
{
    Hashtag* vec = NULL;
    int i = 0;
    Hashtag* x = Tree2Array(root, vec, &i);
    mergesort(x, 0, Ntags - 1);
    printVetor(x);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                       Funcoes Hashtag                                         /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao newHash - Dado um certo nome, correspondente a uma hashtag introduzida pelo utilizador, esta //
// funcao vai criar uma estrutura Hashtag, com esse nome, e com o numero de ocorrencias, que neste     //
// caso, comecara sempre a 1.                                                                          //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

Hashtag newHash(char* nome)
{
    Hashtag hash = (Hashtag)malloc(sizeof(struct hashtag));
    hash->tag = (char*)malloc(sizeof(char)*(strlen(nome) + 1));
    strcpy(hash->tag, nome);
    hash->count = 1;
    return hash;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                   Funcoes Arvore Binaria                                      /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao newNode - Cria um elemento para colocar na arvore, associado a uma determinada hashtag.      //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

Node newNode(Hashtag hash)
{
    Node node = (Node)malloc(sizeof(struct node));
    node->hash = hash;
    node->left = node->right = NULL;
    actualizaMax(node);
    return node;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao insertR - Procura na arvore onde inserir o elemento correspondente a uma hashtag.            //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

Node insertR(Node h, Hashtag hash)
{
    if (h == NULL)
        return newNode(hash);
    else if (less(key(hash), key((h->hash))))
        h->left = insertR(h->left, hash);
    else
        h->right = insertR(h->right, hash);
    return h;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao STinsert - Insere um elemento associado a uma certa hashtag como primeiro elemento da        //
// arvore binaria.                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void STinsert(Node *head, Hashtag hash)
{
    *head = insertR(*head, hash);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao searchR - Procura uma hashtag na arvore binaria, ou seja, se existe algum elemento ja criado //
// associado a essa especifica hashtag.                                                                //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

Node searchR(Node h, Hashtag hash)
{
    if (h == NULL)
        return NULL;
    else if (eq(hash->tag, key(h->hash)))
        return h;
    else if (less(key(hash), key((h->hash))))
        return searchR(h->left, hash);
    else
        return searchR(h->right, hash);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao actualizaMax - Atualiza o elemento Max_node, com a hashtag com o maior numero de ocorrencias //
// para facilitar depois a impressao desta no comando 'm'.
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void actualizaMax(Node x)
{
    if (Max_node == NULL)
        Max_node = x;
    else if ((Max_node->hash)->count == (x->hash)->count)
    {
        if (less(key((x->hash)), key((Max_node->hash))))
            Max_node = x;
    }
    else if ((x->hash)->count > (Max_node->hash)->count)
        Max_node = x;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                   Funcoes Auxiliares                                          /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao split - Recebe o texto introduzido pelo utilizador, separando o texto por palavras.          //
// Posteriormente, verifica se o primeiro elemento da palavra separada e um '#', se for, cria a nova   //
// hashtag, atualizando tanto o numero de ocorrencias de hashtags, como o numero de hashtags distintas //
// se a hashtag encontrada nao tiver sido criada previamente.                                          //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void split(char *line)
{
    char *token = strtok(line, separators);
    lowercase(token);
    Node res_procura;
    while (token != NULL)
    {
        if (token[0] == '#')
        {
            Ntotal += 1;
            Hashtag hash = newHash(token);
            res_procura = searchR(root, hash);
            if (res_procura == NULL)
            {
                STinsert(&root, hash);
                Ntags += 1;
            }
            else
            {
                (res_procura->hash)->count += 1;
                actualizaMax(res_procura);
            }
        }
        token = strtok(NULL, separators);
        lowercase(token);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao lowercase - Funciona para o caso especifico de o utilizador introduzir uma hashtag em        //
// maisculas, convertendo os seus carateres para minusculas, facilitando a ordenacao e introducao      //
// desta hashtag na arvore binaria.                                                                    //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void lowercase(char * c)
{
    int i = 0;
    if (c != NULL)
        for (i = 0; c[i] != '\0'; i++)
            c[i] = tolower(c[i]);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao de Ordenacao - Ordena os elementos do vetor de estruturas dado, tendo em conta o numero de   //
// ocorrencias de cada elemento. Sendo as estruturas de Hashtag, ordena os elementos por ordem         //
// decrescente em relacao ao numero de ocorrencias de cada hashtag.                                    //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void mergesort(Hashtag* vec, int l, int r)
{
    int m = (r + l) / 2;
    if (r <= l)
        return;
    else
    {
        mergesort(vec, l, m);
        mergesort(vec, m + 1, r);
        merge(vec, l, m, r);
    }
}

void merge(Hashtag* vec, int l, int m, int r)
{
    int i, j, k;
    Hashtag*aux = (Hashtag*)malloc(sizeof(Hashtag)*Ntags);
    for (i = m + 1;i>l;i--)
        aux[i - 1] = vec[i - 1];
    for (j = m;j<r;j++)
        aux[r + m - j] = vec[j + 1];
    for (k = l;k <= r;k++)
        if (aux[j]->count > aux[i]->count)
            vec[k] = aux[j--];
        else if (aux[j]->count == aux[i]->count)
        {
            if (strcmp(aux[j]->tag, aux[i]->tag)<0)
                vec[k] = aux[j--];
            else
                vec[k] = aux[i++];
        }
        else
            vec[k] = aux[i++];
    free(aux);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                       Funcoes Vetor                                           /////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao Tree2Array - Recebendo o primeiro elemento de uma arvore binaria, esta funcao percorre       //
// a restante arvore, adicionando os seus elementos a um vetor de estruturas.                          //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

Hashtag* Tree2Array(Node h, Hashtag*vec, int*i)
{
    if (h == NULL)
        return NULL;
    if (vec == NULL)
        vec = newVetor();
    Tree2Array(h->left, vec, i);
    vec[(*i)++] = h->hash;
    Tree2Array(h->right, vec, i);
    return vec;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao newVetor - Cria um novo vetor de estuturas.                                                  //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

Hashtag* newVetor()
{
    Hashtag*vec = (Hashtag*)malloc(sizeof(Hashtag)*Ntags);
    return vec;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funcao printVetor - Imprime os elementos de um dado vetor de estruturas.                            //
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void printVetor(Hashtag* vec)
{
    int i;
    for (i = 0; i < Ntags; i++)
        printf("%s %d\n", vec[i]->tag, vec[i]->count);
}
