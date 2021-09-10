#ifndef PROCESSO_SIMULADOS
#define PROCESSO_SIMULADOS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "gerenciadorProcessos.h"
/*
 * struct para instrucao ao ler o arquivo
 * N x -> intrucao | index
 * D x -> intrucao | index
 * V x y -> intrucao | index | valor
 */
typedef struct Instrucao{
  int index; // caso de N numero de index
  int valor;
  char nomeArquivo[100]; //100 pq numero maximo
  char instrucao;
} Instrucao;

typedef struct ProcessoSimulado{
  int QntdInteiros;
  // int Alocado_V_inteiros;
  // int *Inteiro; //quantidade de inteiros do processo pai
  int ContadorDePrograma;
  int QtdInstrucoes;
  Instrucao* instrucoesPrograma;
} ProcessoSimulado;

void inicializaProcessoSimulado(char* nomeArquivo, ProcessoSimulado *processo);
int contadorInstrucoes(char* nomeArquivo);
int inicializaInstrucoes(char* nomeArquivo, Instrucao* instrucoes, int *qtdInteiros);

#endif