/**
 * Implementacao de uma estrutura pra o processo simulado,
 * nela salvamos todo o arquivo para ser utilizado posteriormente.
 * Assim, fazemos apenas uma leitura no arquivo mantendo todos os 
 * enderecos e valores associados em memoria.
 * 
 * Authors: Vinicius, Arthur, Matheus, Lucas
*/
#ifndef PROCESSO_SIMULADOS
#define PROCESSO_SIMULADOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Instrucao{
  int index; // caso de N numero de index
  int valor;
  char nomeArquivo[100]; //100 pq numero maximo
  char instrucao;
} Instrucao;

typedef struct ProcessoSimulado{
  int QntdInteiros;
  int processoId;
  int *inteirosAlocados; //vetor de inteiros alocados ate o momento eh uma referencia para o vetor de inteiros da CPU
  int ContadorDePrograma; //contador de instrucao do processo
  int QtdInstrucoes;
  int prioridade;
  Instrucao* instrucoesPrograma;
} ProcessoSimulado;

ProcessoSimulado inicializaProcessoSimulado(char* nomeArquivo);
int _contadorInstrucoes(char* nomeArquivo);
int inicializaInstrucoes(char* nomeArquivo, Instrucao** instrucoes, int *qtdInteiros);
void imprimeProcessoSimulado(ProcessoSimulado processo);
#endif