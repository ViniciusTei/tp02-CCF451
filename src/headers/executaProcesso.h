#ifndef EXECUTA_PROCESSOS
#define EXECUTA_PROCESSOS

/*
 * Arquivo destinado para a implementacao dos metodos que vao executar os processos,
 * aqui tambem deve ficar a logica de escalonamento, etc... ??
 * Tive q separar assim por casusa das responsabilidades dos arquivos .h, pra minimizar erros..
*/


#include "gerenciadorProcessos.h"

void executaProximaInstrucaoProcessoSimulado(GerenciadorProcessos *gerenciador);

#endif