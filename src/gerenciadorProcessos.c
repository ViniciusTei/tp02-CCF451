#include "headers/gerenciadorProcessos.h"

void iniciaGerenciadorProcessos(GerenciadorProcessos *gerenciador) {
    inicializaListaVazia(&gerenciador->tabelaProcessos);

    iniciaFilaVazia(&gerenciador->estadoPronto);
    iniciaFilaVazia(&gerenciador->estadoBloqueado);

    gerenciador->estadoExec = 0; //nenhum processo em execucao

    gerenciador->tempoAtual = 0;
    gerenciador->quantidadeProcesos = 0;

    gerenciador->cpu.vetorMemoria = NULL;
    gerenciador->cpu.contadorPrograma = 0;
    gerenciador->cpu.fatiaTempo = 0;
    gerenciador->cpu.unidadesTempoUsadas = 0;


}

void iniciaCPU(GerenciadorProcessos *gerenciador, ProcessoSimulado processo) {
   if (gerenciador->cpu.vetorMemoria != NULL){
       //free(gerenciador->cpu.vetorMemoria);
   }

    gerenciador->cpu.fatiaTempo = 10;
    gerenciador->cpu.contadorPrograma = processo.ContadorDePrograma;
    gerenciador->cpu.quantidadeInteiros = processo.QntdInteiros;

    if (processo.inteirosAlocados != NULL){
        gerenciador->cpu.vetorMemoria = (int *) malloc(sizeof(int) * gerenciador->cpu.quantidadeInteiros);

        for(int i = 0; i < gerenciador->cpu.quantidadeInteiros; i++) {
            gerenciador->cpu.vetorMemoria[i] = processo.inteirosAlocados[i];
        }
    }

    gerenciador->cpu.unidadesTempoUsadas = 0;
}


//todo atualizar impressao
void imprimeCPU(CPU cpu) {
    printf("\n\n------------------------------------------------------\n\n");
    printf("** Dados na CPU **\n\n");

    printf("Contador de programa: %d\n", cpu.contadorPrograma);
    printf("Fatia de tempo: %d\n", cpu.fatiaTempo);

    printf("Memoria atual na CPU: ");
    
    if(cpu.vetorMemoria != NULL) {
        printf("\n");
        for(int i = 0; i < cpu.quantidadeInteiros; i++) {
         printf("index: %d | valor: %d\n", i, cpu.vetorMemoria[i]);
        }
    } else {
        printf("NULL\n");
    }
    

    printf("Unidades de tempo usadas: %d\n", cpu.unidadesTempoUsadas);
}