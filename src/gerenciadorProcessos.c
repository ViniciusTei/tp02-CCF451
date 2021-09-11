#include "headers/gerenciadorProcessos.h"

void iniciaGerenciadorProcessos(GerenciadorProcessos *gerenciador) {
    inicializaListaVazia(&gerenciador->tabelaProcessos);

    iniciaFilaVazia(&gerenciador->estadoPronto);
    iniciaFilaVazia(&gerenciador->estadoBloqueado);

    gerenciador->estadoExec = 0; //nenhum processo em execucao

    gerenciador->tempoCPU = 0;
    gerenciador->quantidadeProcesos = 0;

    gerenciador->cpu.vetorMemoria = NULL;
    gerenciador->cpu.contadorPrograma = 0;
    gerenciador->cpu.fatiaTempo = 0;
    gerenciador->cpu.programa = NULL;
    gerenciador->cpu.unidadesTempoUsadas = 0;


}

void imprimeCPU(CPU cpu) {
    printf("Dados na CPU\n");

    printf("Processo\n");

    imprimeProcessoSimulado(*cpu.programa);

    printf("Contador de programa: %d\n", cpu.contadorPrograma);
    printf("Fatia de tempo: %d\n", cpu.fatiaTempo);

    printf("Memoria atual na CPU: \n");
    for(int i = 0; i <sizeof(cpu.vetorMemoria); i++) {
        printf("index: %d | valor: %d\n", i, cpu.vetorMemoria[i]);
    }

    printf("Unidades de tempo usadas: %d\n", cpu.unidadesTempoUsadas);
}