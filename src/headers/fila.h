#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct TipoCelula  *TipoApontadorCelulaFila;
typedef struct TipoCelula {
  int indiceTabelaProcessos;
  TipoApontadorCelulaFila *Prox;
} TipoCelula;

typedef struct TipoFila {
  TipoCelula *Frente, *Tras;
} TipoFila;

void iniciaFilaVazia(TipoFila *Fila);
int isFilaVazia(TipoFila Fila);
void insereNaFila(int x, TipoFila *Fila);
int removeDaFila(TipoFila *Fila);
void imprimeFila(TipoFila Fila);