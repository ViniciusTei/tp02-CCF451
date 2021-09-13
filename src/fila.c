#include "headers/fila.h"

/*
 * Function:  iniciaFilaVazia 
 * 
 * Inicia uma fila vazia.
 *
 * @params:
 * *Fila: fila que vamos trabalhar
 *
 *  returns: void
 */
void iniciaFilaVazia(TipoFila *Fila) { 
    Fila->Frente = (TipoApontadorCelulaFila) malloc(sizeof(TipoCelula));
    Fila->Tras = Fila->Frente;
    Fila->Frente->Prox = NULL;
} 

/*
 * Function:  isFilaVazia 
 * 
 * Verifica se uma fila eh vazia.
 *
 * @params:
 * Fila: fila que vamos trabalhar
 *
 *  returns: 
 *   0 se fila nao esta vazia
 *   1 se a fila esta vazia
 */
int isFilaVazia(TipoFila Fila) { 
    return (Fila.Frente == Fila.Tras); 
} 

/*
 * Function:  insereNaFila 
 * 
 * Insere um item na fila, seguindo uma ordem de prioridades.
 *
 * @params:
 *  x: item para ser inserido
 * *Fila: fila que vamos inserir
 *
 *  returns: void
 */
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

/*
 * Function:  removeDaFila 
 * 
 * Desenfileiramos o primeiro da fila.
 *
 * @params:
 * *Fila: fila que vamos trabalhar
 *
 *  returns: indece, na tabela de processos, do item removido 
 */
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

/*
 * Function:  imprimeFila 
 * 
 * Imprime os indeces armazenados na fila
 *
 * @params:
 * Fila: fila que vamos trabalhar
 *
 *  returns: void
 */
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