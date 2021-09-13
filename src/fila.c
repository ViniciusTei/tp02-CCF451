#include "headers/fila.h"

void iniciaFilaVazia(TipoFila *Fila) { 
    Fila->Frente = (TipoApontadorCelulaFila) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
} 

int isFilaVazia(TipoFila Fila) { 
    return (Fila.Frente == Fila.Tras); 
} 

void insereNaFila(TipoItem x, TipoFila *Fila) { 
    TipoCelula *Proximo, *Anterior, *novo;
    Proximo = Fila->Frente->Prox;
    
    novo = (TipoApontadorCelulaFila) malloc(sizeof(TipoCelula));
    novo->item = x;

    Anterior = Fila->Frente;
    //busca na fila um item com prioridade menor, caso contrario insere no final
    while (Proximo != NULL && *Proximo->item.prioridade < *x.prioridade) { 

        Anterior = Proximo;
        Proximo = Proximo->Prox;
    }

    novo->Prox = Proximo;
    Anterior->Prox = novo;

    if(Proximo == NULL) {
        Fila->Tras = Anterior->Prox;
    }
} 

int removeDaFila(TipoFila *Fila) { 
    TipoCelula *aux;
    TipoItem Item;
    
    if (isFilaVazia(*Fila)) { 
        printf("Erro fila esta vazia\n"); 
        return -1; 
    }

    aux = Fila->Frente;
    Fila->Frente = Fila->Frente->Prox;
    Item = Fila->Frente->item;
    free(aux);

    return Item.indeceTabelaProcessos;
} 

void imprimeFila(TipoFila Fila)
{ 
    printf("Imprimindo fila: \n");
    TipoCelula *Aux;
    Aux = Fila.Frente->Prox;
    while (Aux != NULL) { 
        printf("%d\n", Aux->item.indeceTabelaProcessos);
        Aux = Aux->Prox;
    }
}