#include "Headers/fila.h"

void iniciaFilaVazia(TipoFila *Fila) { 
    Fila->Frente = (TipoApontadorCelulaFila) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
} 

int isFilaVazia(TipoFila Fila) { 
    return (Fila.Frente == Fila.Tras); 
} 

void insereNaFila(int x, TipoFila *Fila) { 
    Fila->Tras->Prox = (TipoApontadorCelulaFila) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Tras->Prox;
    Fila->Tras->indiceTabelaProcessos = x;
    Fila->Tras->Prox = NULL;
} 

int removeDaFila(TipoFila *Fila) { 
    TipoCelula *aux;
    int Item;
    
    if (isFilaVazia(*Fila)) { 
        printf("Erro fila esta vazia\n"); 
        return; 
    }

    aux = Fila->Frente;
    Fila->Frente = Fila->Frente->Prox;
    Item = Fila->Frente->indiceTabelaProcessos;
    free(aux);

    return Item;
} 

void imprimeFila(TipoFila Fila)
{ 
    TipoCelula *Aux;
    Aux = Fila.Frente->Prox;
    while (Aux != NULL) { 
        printf("%d\n", Aux->indiceTabelaProcessos);
        Aux = Aux->Prox;
    }
}