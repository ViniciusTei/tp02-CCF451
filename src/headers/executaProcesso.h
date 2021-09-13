/*
 * Arquivo destinado para a implementacao dos metodos que vao executar os processos,
 * aqui esta a logica de escalonamento
 * 
 * Authors: Vinicius, Arthur, Matheus, Lucas
 * 
*/
#ifndef EXECUTA_PROCESSOS
#define EXECUTA_PROCESSOS

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