/**
 * Implementacao de uma estrutura para o gerenciador de processos
 * 
 * Authors: Vinicius, Arthur, Matheus, Lucas
*/
#ifndef PROCESSO_GERENCIADOR
#define PROCESSO_GERENCIADOR

#include "tabelaDeProcessos.h"
#include "fila.h"

typedef struct CPU {
    int contadorPrograma;
    int *vetorMemoria;
    int fatiaTempo;
    int unidadesTempoUsadas;
    int quantidadeInteiros;
    Processo *processoAtual;
} CPU;

typedef struct GerenciadorProcessos {
    TipoFila estadoPronto, estadoBloqueado;
    int estadoExec;
    TabelaDeProcessos tabelaProcessos;
    CPU cpu;
    int tempoAtual; //tempo global atual
    int quantidadeProcesos;
} GerenciadorProcessos;

void iniciaGerenciadorProcessos(GerenciadorProcessos *gerenciador);
void iniciaCPU(GerenciadorProcessos *gerenciador, ProcessoSimulado processo);
void imprimeCPU(CPU cpu);

#endif