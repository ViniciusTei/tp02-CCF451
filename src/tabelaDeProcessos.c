#include "headers/tabelaDeProcessos.h"

void inicializaListaVazia(TabelaDeProcessos *lista) {
    lista->Primeiro = 0;
    lista->Ultimo = lista->Primeiro;
}

int isListaVazia(TabelaDeProcessos Lista) { 
    return (Lista.Primeiro == Lista.Ultimo);
}  /* Vazia */

void insereNaLista(Processo x, TabelaDeProcessos *Lista) { 
    if (Lista -> Ultimo > MAXTAM) {
        printf("Lista esta cheia\n");
    } else { 
        Lista -> Item[Lista -> Ultimo] = x;
        Lista -> Ultimo++;
    }
}  /* Insere */

void retiraDaLista(int indexToRemove, TabelaDeProcessos *Lista) { 

    if (isListaVazia(*Lista) || indexToRemove >= Lista -> Ultimo) { 
        printf(" Erro   Posicao nao existe\n");
        return;
    }

    Lista -> Ultimo--;                 
    for (int i = indexToRemove; i < Lista -> Ultimo; i++)
        Lista -> Item[i] = Lista -> Item[i + 1];

}  /* Retira */

void imprimeLista(TabelaDeProcessos Lista) { 
    for (int i = Lista.Primeiro; i < (Lista.Ultimo); i++) {
        printf("%d\n", Lista.Item[i].processoId);

    }
}  /* Imprime */