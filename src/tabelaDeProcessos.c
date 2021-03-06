#include "headers/tabelaDeProcessos.h"

/*
 * Function:  inicializaListaVazia 
 * 
 * Inicia a tabela de processo vazia.
 *
 * @params:
 * lista: tabela de processos que vamos trabalhar
 *
 *  returns: void
 */
void inicializaListaVazia(TabelaDeProcessos *lista) {
    lista->Primeiro = 0;
    lista->Ultimo = lista->Primeiro;
}

/*
 * Function:  isListaVazia
 * 
 * Funcao que verifica se uma lista esta vazia.
 *
 * @params:
 * lista: tabela de processos que vamos trabalhar
 *
 *  returns: 
 *      1 se a lista esta vazia
 *      0 se a lista tem algum conteudo
 */
int isListaVazia(TabelaDeProcessos Lista) { 
    return (Lista.Primeiro == Lista.Ultimo);
}

/*
 * Function:  insereNaLista
 * 
 * Inserimos um novo processo na tabela
 *
 * @params:
 * x: itens da tabela de processos que queremos inserir
 * Lista: tabela de processos que vamos trabalhar
 *
 *  returns: indice do item inserido
 */
int insereNaLista(Processo x, TabelaDeProcessos *Lista) { 
    if (Lista -> Ultimo > MAXTAM) {
        printf("Lista esta cheia\n");
    } else { 
        Lista -> Item[Lista -> Ultimo] = x;
        Lista -> Ultimo++;
    }

    return Lista->Ultimo - 1;
}

/*
 * Function:  retiraDaLista
 * 
 * Removemos um item de um determinado indice
 *
 * @params:
 * indexToRemove: index do item que queremos remover
 * Lista: tabela de processos que vamos trabalhar
 *
 *  returns: void
 */
void retiraDaLista(int indexToRemove, TabelaDeProcessos *Lista) { 

    if (isListaVazia(*Lista) || indexToRemove >= Lista -> Ultimo) { 
        printf(" Erro   Posicao nao existe\n");
        return;
    }

    Lista -> Ultimo--;                 
    for (int i = indexToRemove; i < Lista -> Ultimo; i++)
        Lista -> Item[i] = Lista -> Item[i + 1];

} 

/*
 * Function:  retiraDaLista
 * 
 * Imprime a tabela de processos formatada
 *
 * @params:
 * Lista: tabela de processos que vamos trabalhar
 *
 *  returns: void
 */
void imprimeLista(TabelaDeProcessos Lista) {
    printf("\n\n------------------------------------------------------\n\n");
    printf("** Dados da Tabela de Processos ** \n\n");
    for (int i = Lista.Primeiro; i < (Lista.Ultimo); i++) {
        //imprimeProcessoSimulado(*Lista.Item[i].processo);
        printf("\n------------------------------------------------------\n");
        printf("Processo n??mero: %d\n", i);
        printf("ID do Processo: %d\n", Lista.Item[i].processoId);
        printf("ID do Processo Pai: %d\n", Lista.Item[i].processoPaiId);

        printf("Tempo inicio de processo: %d\n", Lista.Item[i].tempoInicio);
        printf("Tempo total da CPU: %d\n", Lista.Item[i].tempoCpu);

        switch (Lista.Item[i].estados){
            case Bloqueado:
                printf("Estado do processo: Bloqueado\n");
                break;
            case Pronto:
                printf("Estado do processo: Pronto\n");
                break;
            case Execucao:
                printf("Estado do processo: Em Execu????o\n");
                break;
            default:
                break;
        }
        
        printf("Prioridade do processo: %d\n", Lista.Item[i].prioridade);
        printf("Contador de programa do processo: %d\n", Lista.Item[i].processo.ContadorDePrograma);
        printf("Quantide de instru????es do processo: %d\n", Lista.Item[i].processo.QtdInstrucoes);
        printf("Quantide de inteiros do processo: %d\n", Lista.Item[i].processo.QntdInteiros);
        //printf("Tipo Instru????o: %d\n", Lista.Item[i].processo->instrucoesPrograma->instrucao);

        printf("Vetor de inteiros alocados:");
        if(Lista.Item[i].processo.inteirosAlocados == NULL) {
            printf("NULL\n");
        } else {
            printf("\n");
            for(int j = 0; j < Lista.Item[i].processo.QntdInteiros; j++){
                printf("Valor inteiro da variavel n??mero %d: %d\n", j, Lista.Item[i].processo.inteirosAlocados[j]) ;
            }
        }
        

        printf("Instru????es:\n");
        for (int z = 0; z < Lista.Item[i].processo.QtdInstrucoes; z++){
            switch (Lista.Item[i].processo.instrucoesPrograma[z].instrucao){
                case 'N':
                    printf("Instru????o N    Numero de Variaveis: %d\n", Lista.Item[i].processo.instrucoesPrograma[z].index);
                    break;
                case 'D':
                    printf("Instru????o D    Index: %d\n", Lista.Item[i].processo.instrucoesPrograma[z].index);
                    break;
                case 'V':
                    printf("Instru????o V    Index: %d    Valor: %d\n", Lista.Item[i].processo.instrucoesPrograma[z].index, 
                    Lista.Item[i].processo.instrucoesPrograma[z].valor);
                    break;
                case 'A':
                    printf("Instru????o A    Index: %d    Valor: %d\n", Lista.Item[i].processo.instrucoesPrograma[z].index, 
                    Lista.Item[i].processo.instrucoesPrograma[z].valor);
                    break;
                case 'S':
                    printf("Instru????o S    Index: %d    Valor: %d\n", Lista.Item[i].processo.instrucoesPrograma[z].index,
                    Lista.Item[i].processo.instrucoesPrograma[z].valor);
                    break;
                case 'F':
                    printf("Instru????o F    Quantidade de instru????es: %d\n", Lista.Item[i].processo.instrucoesPrograma[z].index);
                    break;
                case 'R':
                    printf("Instru????o R    Nome do arquivo: %s\n", Lista.Item[i].processo.instrucoesPrograma[z].nomeArquivo);
                    break;
                default:
                    break;
            }
        }
    }
    
    printf("\n------------------------------------------------------\n");
}

