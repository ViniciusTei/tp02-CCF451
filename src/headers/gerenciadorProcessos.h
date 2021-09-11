#ifndef PROCESSO_GERENCIADOR
#define PROCESSO_GERENCIADOR

#include "tabelaDeProcessos.h"
#include "fila.h"

typedef struct CPU{
    ProcessoSimulado *programa;
    int contadorPrograma;
    int *vetorMemoria;
    int fatiaTempo;
    int unidadesTempoUsadas;
} CPU;

typedef struct GerenciadorProcessos {
    TipoFila estadoPronto, estadoBloqueado;
    int estadoExec;
    TabelaDeProcessos tabelaProcessos;
    CPU cpu;
    int tempoCPU; //tempo global atual
    int quantidadeProcesos;
} GerenciadorProcessos;

void iniciaGerenciadorProcessos(GerenciadorProcessos *gerenciador);
void imprimeCPU(CPU cpu);
#endif