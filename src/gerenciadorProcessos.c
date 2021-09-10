#include "headers/gerenciadorProcessos.h"

void iniciaGerenciadorProcessos(GerenciadorProcessos *gerenciador) {
    inicializaListaVazia(&gerenciador->tabelaProcessos);

    iniciaFilaVazia(&gerenciador->estadoPronto);
    iniciaFilaVazia(&gerenciador->estadoBloqueado);

    gerenciador->estadoExec = 0; //nenhum processo em execucao

    gerenciador->tempoCPU = 0;

    gerenciador->cpu.vetorMemoria = NULL;

}