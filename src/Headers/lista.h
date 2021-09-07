#include <stdio.h>
#include <stdlib.h>

#define MAXTAM 1000

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
} TipoLista;

void inicializaListaVazia(TipoLista *lista);
int isListaVazia(TipoLista Lista);
void insereNaLista(TipoItem x, TipoLista *Lista);
void retiraDaLista(int indexToRemove, TipoLista *Lista);
void imprimeLista(TipoLista Lista);