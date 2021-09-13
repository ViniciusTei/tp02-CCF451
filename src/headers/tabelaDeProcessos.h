/**
 * Implementacao de uma estrutura para a tabela de processos,
 * utilizamos a estrutura de Lista para auxiliar nos processos
 * de inserir e remover.
 * 
 * Authors: Vinicius, Arthur, Matheus, Lucas
*/
#ifndef TABELA_PROCESSOS
#define TABELA_PROCESSOS

#include "processoSimulados.h"

#define MAXTAM 1000

typedef enum Estados {
    Bloqueado = 0, 
    Pronto, 
    Execucao
} Estados;

typedef struct Processo {
    pid_t processoId;
    pid_t processoPaiId;
    int contadorPrograma; 
    ProcessoSimulado processo;
    int prioridade;
    Estados estados;
    int tempoInicio;
    int tempoCpu;
} Processo;

typedef struct {
  Processo Item[MAXTAM];
  int Primeiro, Ultimo;
} TabelaDeProcessos;

void inicializaListaVazia(TabelaDeProcessos *lista);
int isListaVazia(TabelaDeProcessos Lista);
int insereNaLista(Processo x, TabelaDeProcessos *Lista);
void retiraDaLista(int indexToRemove, TabelaDeProcessos *Lista);
void imprimeLista(TabelaDeProcessos Lista);

#endif