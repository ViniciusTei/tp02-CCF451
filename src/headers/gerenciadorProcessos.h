#include "tabelaDeProcessos.h"
#include "fila.h"

typedef struct CPU{
    ProcessoSimulado *vetorDePrograma;
    int contadorPrograma;
    int *vetorMemoria;
    int fatiaTempo;
    int unidadesTempoUsadas;
    //numero de unidades de tempo usadas, ate entao, na fatia de tempo atual????
} CPU;

typedef struct GerenciadorProcessos {
    //Tempo, Cpu, TabelaDeProcessos, EstadoPronto, EstadoBloqueado e EstadoExecução.
    TipoFila estadoPronto, estadoBloqueado;
    int estadoExec;
    TabelaDeProcessos tabelaProcessos;
    CPU cpu;
    int tempoCPU;
} GerenciadorProcessos;

void iniciaGerenciadorProcessos(GerenciadorProcessos *gerenciador);