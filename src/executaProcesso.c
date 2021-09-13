#include "headers/executaProcesso.h"

void controleEscalonamento(GerenciadorProcessos *gerenciador) {
  ProcessoSimulado *processoEmExecucao;
  TipoItem x;
  int flagPrioridadeAlterada = FALSE;
  
  executaProximaInstrucaoProcessoSimulado(gerenciador);

  gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade = gerenciador->cpu.processoAtual->prioridade;
  
  if(gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade == MUITO_ALTA) {

    
    gerenciador->cpu.unidadesTempoUsadas++; //atualiza uma unidade de tempo 

    if(gerenciador->cpu.unidadesTempoUsadas >= gerenciador->cpu.fatiaTempo) {
      gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade = ALTA; //muda a prioridade do processo
      flagPrioridadeAlterada = TRUE;
    } 

  } else if(gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade == ALTA) {
    
    gerenciador->cpu.unidadesTempoUsadas+=2; //atualiza uma unidade de tempo

    if(gerenciador->cpu.unidadesTempoUsadas >= gerenciador->cpu.fatiaTempo) {
      gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade = MEDIA; //muda a prioridade do processo
      flagPrioridadeAlterada = TRUE;
    } 
  } else if(gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade == MEDIA) {
    gerenciador->cpu.unidadesTempoUsadas+=4; //atualiza uma unidade de tempo 

    if(gerenciador->cpu.unidadesTempoUsadas >= gerenciador->cpu.fatiaTempo) {
      gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade = BAIXA; //muda a prioridade do processo
      flagPrioridadeAlterada = TRUE;
    }
  } else if(gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade == BAIXA) {
    
    gerenciador->cpu.unidadesTempoUsadas+=8; //atualiza uma unidade de tempo 

    if(gerenciador->cpu.unidadesTempoUsadas >= gerenciador->cpu.fatiaTempo) {
      gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade = BAIXA; //muda a prioridade do processo
      flagPrioridadeAlterada = TRUE;
    }
  }

  if(flagPrioridadeAlterada && gerenciador->tabelaProcessos.Ultimo > 1) {
    //buscar processo com prioriade maior
    //printf("Prioridade alterada\n");
    int index = verificaPrioridadeProcessos(gerenciador, gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade);

    //printf("Em execucao: %d | Proximo: %d \n", gerenciador->estadoExec, index);
    if(index > -1) {
      trocaContexto(gerenciador);
      //printf("Troca de contexto feita\n");

      gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Pronto;

      //printf("Esdato %d\n", gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados);
      x.indeceTabelaProcessos = gerenciador->estadoExec;
      x.prioridade = &gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade;

      insereNaFila(x, &gerenciador->estadoPronto);
      //printf("Inseriu\n");
      imprimeFila(gerenciador->estadoPronto);

      int removido = removeDaFila(&gerenciador->estadoPronto); //removendo index da fila, pois tem prioridade mais alta

      gerenciador->tabelaProcessos.Item[removido].estados = Execucao;
      gerenciador->estadoExec = removido;

      //printf("Index %d | Removido %d\n", index, removido);

      //imprimeLista(gerenciador->tabelaProcessos);

      //printf("Instrucao: %d\n", gerenciador->tabelaProcessos.Item[removido].processo.processoId);
      iniciaCPU(gerenciador, gerenciador->tabelaProcessos.Item[removido].processo);    
      gerenciador->cpu.processoAtual = &gerenciador->tabelaProcessos.Item[gerenciador->estadoExec];
      //trocaContexto(gerenciador);
    }
  }
  
  
}

int verificaPrioridadeProcessos(GerenciadorProcessos *gerenciador, Prioridade prioridade) {
    
    for(int i = 0; i < gerenciador->tabelaProcessos.Ultimo; i++) {
      if(gerenciador->tabelaProcessos.Item[i].prioridade <= prioridade && gerenciador->tabelaProcessos.Item[i].estados != Execucao) {
        return i; //retorna index do processo a ser executado
      }
    }

    return -1;
}

void executaProximaInstrucaoProcessoSimulado(GerenciadorProcessos *gerenciador) {
  Instrucao instrucaoAtual;
  int tamanho, removidoBloqueado, removidoPronto;
  ProcessoSimulado novoProcessoSimulado;
  Processo novoProcesso;
  TipoItem x;
  int indexTabela;
  char strArquivo[100];
  
  instrucaoAtual = gerenciador->cpu.processoAtual->processo.instrucoesPrograma[gerenciador->cpu.contadorPrograma];

  printf("\nInstrucao atual: %c\n", instrucaoAtual.instrucao);
  
  switch (instrucaoAtual.instrucao)
  {
  case 'N':
    gerenciador->cpu.quantidadeInteiros = instrucaoAtual.index;
   
    gerenciador->cpu.contadorPrograma++;
    gerenciador->tempoAtual++;
    break;
  case 'D':
    tamanho = instrucaoAtual.index + 1; 

    if(gerenciador->cpu.vetorMemoria == NULL) {
      gerenciador->cpu.vetorMemoria = (int *) malloc(sizeof(int) * tamanho);
    } else {
      gerenciador->cpu.vetorMemoria = (int *) realloc(gerenciador->cpu.vetorMemoria, sizeof(int) * tamanho);
    }

    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = 0;

    gerenciador->cpu.contadorPrograma++;
    gerenciador->tempoAtual++;
    break;
  case 'V':
    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = instrucaoAtual.valor;

    gerenciador->tempoAtual++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'A':
    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = gerenciador->cpu.vetorMemoria[instrucaoAtual.index] + instrucaoAtual.valor;

    gerenciador->tempoAtual++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'S':
    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = gerenciador->cpu.vetorMemoria[instrucaoAtual.index] - instrucaoAtual.valor;

    gerenciador->tempoAtual++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'B':

    trocaContexto(gerenciador);

    gerenciador->cpu.processoAtual->estados = Bloqueado;
    
    
    x.indeceTabelaProcessos = gerenciador->estadoExec;
    x.prioridade = &gerenciador->cpu.processoAtual->processo.prioridade;
    
    insereNaFila(x, &gerenciador->estadoBloqueado);

    removidoBloqueado = removeDaFila(&gerenciador->estadoBloqueado);

    x.indeceTabelaProcessos = removidoBloqueado;
    x.prioridade = &gerenciador->tabelaProcessos.Item[removidoBloqueado].prioridade;

    insereNaFila(x, &gerenciador->estadoPronto);

    removidoPronto = removeDaFila(&gerenciador->estadoPronto);

    if(removidoPronto > -1) {
      gerenciador->estadoExec = removidoPronto;

      gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Execucao;

      iniciaCPU(gerenciador, gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processo);
      gerenciador->cpu.processoAtual = &gerenciador->tabelaProcessos.Item[gerenciador->estadoExec];
    }

    gerenciador->tempoAtual++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'T':
    
    //retiraDaLista(gerenciador->estadoExec, &gerenciador->tabelaProcessos);
    trocaContexto(gerenciador);
    
    free(gerenciador->cpu.vetorMemoria);

    removidoPronto = removeDaFila(&gerenciador->estadoPronto);

    if(removidoPronto > -1) {
      gerenciador->estadoExec = removidoPronto;

      gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Execucao;

      iniciaCPU(gerenciador, gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processo);
      gerenciador->cpu.processoAtual = &gerenciador->tabelaProcessos.Item[gerenciador->estadoExec];
    }

    gerenciador->tempoAtual++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'F': 
    novoProcesso.processo.processoId = gerenciador->tabelaProcessos.Ultimo;
    novoProcesso.processo.ContadorDePrograma = gerenciador->cpu.contadorPrograma;

    novoProcesso.processo.inteirosAlocados = (int *) malloc(sizeof(int) * gerenciador->cpu.quantidadeInteiros);

    for(int j = 0; j < gerenciador->cpu.quantidadeInteiros; j++) {
      novoProcesso.processo.inteirosAlocados[j] = gerenciador->cpu.vetorMemoria[j];
    }

    novoProcesso.processo.QntdInteiros = gerenciador->cpu.processoAtual->processo.QntdInteiros;
    
    novoProcesso.processo.QtdInstrucoes = gerenciador->cpu.processoAtual->processo.QtdInstrucoes;
    novoProcesso.processo.instrucoesPrograma = (Instrucao *) malloc(sizeof(Instrucao) * novoProcesso.processo.QtdInstrucoes);

    for(int i = 0; i < novoProcesso.processo.QtdInstrucoes; i++) {
      novoProcesso.processo.instrucoesPrograma[i].index = gerenciador->cpu.processoAtual->processo.instrucoesPrograma[i].index;
      novoProcesso.processo.instrucoesPrograma[i].instrucao = gerenciador->cpu.processoAtual->processo.instrucoesPrograma[i].instrucao;
      novoProcesso.processo.instrucoesPrograma[i].valor = gerenciador->cpu.processoAtual->processo.instrucoesPrograma[i].valor;
      strcpy(novoProcesso.processo.instrucoesPrograma[i].nomeArquivo, gerenciador->cpu.processoAtual->processo.instrucoesPrograma[i].nomeArquivo);

    }
    
    gerenciador->cpu.contadorPrograma++; //proxima
    gerenciador->cpu.contadorPrograma += instrucaoAtual.index; //n instrucoes depois da proxima
    
    novoProcesso.processo.ContadorDePrograma++;
    novoProcesso.processoPaiId = gerenciador->cpu.processoAtual->processoId;
    novoProcesso.processoId = novoProcesso.processo.processoId;
    novoProcesso.tempoInicio = gerenciador->tempoAtual;
    novoProcesso.tempoCpu = 0;
    novoProcesso.estados = Pronto;
    // novoProcesso.contadorPrograma = novoProcessoSimulado.ContadorDePrograma;
    novoProcesso.prioridade = gerenciador->cpu.processoAtual->prioridade;

    indexTabela = insereNaLista(novoProcesso, &gerenciador->tabelaProcessos);

    //imprimeLista(gerenciador->tabelaProcessos);

    x.indeceTabelaProcessos = indexTabela;
    x.prioridade = &novoProcesso.prioridade;

    insereNaFila(x, &gerenciador->estadoPronto);

    gerenciador->tempoAtual++;
    gerenciador->quantidadeProcesos++;
    break;
  case 'R':

    printf("R\n");
    //inicializamos novo processo com o mesmo arquivo
    strcpy(strArquivo, "./Arquivos/");
    strcat(strArquivo, instrucaoAtual.nomeArquivo);
    
    inicializaProcessoSimulado(strArquivo, &novoProcesso.processo);
    imprimeProcessoSimulado(novoProcessoSimulado);
    
    gerenciador->quantidadeProcesos++;
    
    novoProcesso.processoId = gerenciador->cpu.processoAtual->processoId + 1;
    novoProcesso.processoPaiId = gerenciador->cpu.processoAtual->processoId;
    novoProcesso.contadorPrograma = novoProcesso.processo.ContadorDePrograma;
    //novoProcesso.processo = &novoProcessoSimulado;
    novoProcesso.estados = Pronto;
    novoProcesso.tempoInicio = gerenciador->tempoAtual;
    novoProcesso.tempoCpu = 0;
    novoProcesso.prioridade = MUITO_ALTA;

    indexTabela = insereNaLista(novoProcesso, &gerenciador->tabelaProcessos); //insere processo na tabela de processos
    
    x.indeceTabelaProcessos = indexTabela;
    x.prioridade = &novoProcesso.prioridade;
    
    insereNaFila(x, &gerenciador->estadoPronto);
        
    gerenciador->estadoExec = removeDaFila(&gerenciador->estadoPronto);  

    iniciaCPU(&gerenciador, novoProcessoSimulado);      
    gerenciador->cpu.processoAtual = &gerenciador->tabelaProcessos.Item[gerenciador->estadoExec]; 

    gerenciador->cpu.processoAtual->estados = Execucao;

    gerenciador->cpu.contadorPrograma = 0;

    free(gerenciador->cpu.vetorMemoria);

    gerenciador->tempoAtual++;
    break;
  default:
    break;
  }

}

void executaProcessoImpressao(GerenciadorProcessos gerenciador, int imprimeTempoMedio) {
  
  imprimeCPU(gerenciador.cpu);
  imprimeLista(gerenciador.tabelaProcessos);

  if(imprimeTempoMedio) {
    double tempo;
    tempo = gerenciador.tempoAtual / gerenciador.quantidadeProcesos;

    printf("Tempo medio do ciclo: %.2lf\n\n", tempo);
  }
}

void trocaContexto(GerenciadorProcessos *gerenciador) {

  gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processo.ContadorDePrograma = gerenciador->cpu.contadorPrograma;
  gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processo.QntdInteiros = gerenciador->cpu.quantidadeInteiros;
  // memcpy(gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processo->inteirosAlocados, gerenciador->cpu.vetorMemoria, sizeof(gerenciador->cpu.vetorMemoria));
  gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].tempoCpu = gerenciador->cpu.unidadesTempoUsadas;
  gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processo.inteirosAlocados = (int *) malloc(sizeof(int) * gerenciador->cpu.quantidadeInteiros);
  //gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade = gerenciador->cpu.processoAtualSimulado->prioridade;

  for(int i = 0; i < gerenciador->cpu.quantidadeInteiros; i++) {
    gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processo.inteirosAlocados[i] = gerenciador->cpu.vetorMemoria[i];
    printf("alocou: %d\n", gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processo.inteirosAlocados[i]);
  }
  
}
