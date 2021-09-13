#include "headers/gerenciadorProcessos.h"

/*
 * Function:  iniciaGerenciadorProcessos 
 * 
 * Inicia as estrutura do gerenciador de processos
 *
 * @params:
 * gerenciador: gerenciador com as estruturas que vamos trabalhar
 *
 *  returns: void
 */
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

/*
 * Function:  iniciaCPU 
 * 
 * Copia os dados do processo simulado dado para a cpu
 *
 * @params:
 * gerenciador: gerenciador com as estruturas que vamos trabalhar
 * processo: processo simulado que queremos copiar
 *
 *  returns: void
 */
void iniciaCPU(GerenciadorProcessos *gerenciador, ProcessoSimulado processo) {
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


/*
 * Function:  imprimeCPU 
 * 
 * Imprime os dados da cpu formatdos
 *
 * @params:
 * cpu: cpu com os dados que queremos mostrar
 *
 *  returns: void
 */
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