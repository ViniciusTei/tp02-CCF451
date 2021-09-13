#ifndef EXECUTA_PROCESSOS
#define EXECUTA_PROCESSOS

/*
 * Arquivo destinado para a implementacao dos metodos que vao executar os processos,
 * aqui tambem deve ficar a logica de escalonamento, etc... ??
 * Tive q separar assim por casusa das responsabilidades dos arquivos .h, pra minimizar erros..
*/


#include "gerenciadorProcessos.h"

#define TRUE 1
#define FALSE 0

typedef enum Prioridade {
    MUITO_ALTA, ALTA, MEDIA, BAIXA
} Prioridade;

void controleEscalonamento(GerenciadorProcessos *gerenciador);
void executaProximaInstrucaoProcessoSimulado(GerenciadorProcessos *gerenciador);
void executaProcessoImpressao(GerenciadorProcessos gerenciador, int imprimeTempoMedio);
void trocaContexto(GerenciadorProcessos *gerenciador);
int verificaPrioridadeProcessos(GerenciadorProcessos *gerenciador, Prioridade prioridade);

#endif