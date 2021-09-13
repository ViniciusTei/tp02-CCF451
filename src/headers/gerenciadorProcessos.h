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
    Processo *processoAtual; //incluir estrutura do Processo aqui
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