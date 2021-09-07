#include <stdio.h>
#include <stdlib.h>
#include "processoSimulados.h"

#define MAXTAM 1000

typedef struct ProcessoSimulado {
    
}ProcessoSimulado;

enum Estados {
    Bloqueado = 0, 
    Pronto, 
    Execucao
} Estados;

typedef struct CPU{
    ProcessoSimulado *vetorDePrograma;
    int contadorPrograma;
    int vetorMemoria[1024];
    int unidadeDeTempo;
} CPU;

TipoFila EstadoPronto, EstadoBloqueado;
int EstadoExec;

typedef struct Processo {
    pid_t processoId;
    pid_t processoPaiId;
    int *contadorPrograma; // veriicar se vai ser preciso mesmo
    ProcessoSimulado *processo;
    int prioridade;
    Estados estados;
    int tempoInicio;
    int tempoCpu;
} Processo;

typedef struct {
  Processo Item[MAXTAM]; // Substituir pelo tipo da Tabela de processos
  int Primeiro, Ultimo;
} TabelaDeProcessos;

void inicializaListaVazia(TabelaDeProcessos *lista);
int isListaVazia(TabelaDeProcessos Lista);
void insereNaLista(TipoItem x, TabelaDeProcessos *Lista);
void retiraDaLista(int indexToRemove, TabelaDeProcessos *Lista);
void imprimeLista(TabelaDeProcessos Lista);