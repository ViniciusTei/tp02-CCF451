#include "headers/executaProcesso.h"

void executaProximaInstrucaoProcessoSimulado(GerenciadorProcessos *gerenciador) {
  Instrucao instrucaoAtual;
  int tamanho, removidoBloqueado, removidoPronto;
  ProcessoSimulado *novoProcessoSimulado;
  Processo novoProcesso;

  instrucaoAtual = gerenciador->cpu.programa->instrucoesPrograma[gerenciador->cpu.programa->ContadorDePrograma];

  printf("\nInstrucao atual: %c\n", gerenciador->cpu.programa->instrucoesPrograma[gerenciador->cpu.programa->ContadorDePrograma].instrucao);
  

  switch (instrucaoAtual.instrucao)
  {
  case 'N':
    gerenciador->cpu.programa->QntdInteiros =  instrucaoAtual.index;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'D':
    tamanho = instrucaoAtual.index + 1; 

    if(gerenciador->cpu.vetorMemoria == NULL) {
      gerenciador->cpu.vetorMemoria = (int *) malloc(sizeof(int) * tamanho);
      gerenciador->cpu.programa->inteirosAlocados = (int *) malloc(sizeof(int) * tamanho);
    } else {
      gerenciador->cpu.vetorMemoria = (int *) realloc(gerenciador->cpu.vetorMemoria, sizeof(int) * tamanho);
      gerenciador->cpu.programa->inteirosAlocados = (int *) realloc(gerenciador->cpu.programa->inteirosAlocados, sizeof(int) * tamanho);
    }

    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = 0;
    gerenciador->cpu.programa->inteirosAlocados[instrucaoAtual.index] = 0;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'V':
    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = instrucaoAtual.valor;
    gerenciador->cpu.programa->inteirosAlocados[instrucaoAtual.index] = instrucaoAtual.valor;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'A':
    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = gerenciador->cpu.vetorMemoria[instrucaoAtual.index] + instrucaoAtual.valor;
    gerenciador->cpu.programa->inteirosAlocados[instrucaoAtual.index] = gerenciador->cpu.programa->inteirosAlocados[instrucaoAtual.index] + instrucaoAtual.valor;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'S':
    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = gerenciador->cpu.vetorMemoria[instrucaoAtual.index] - instrucaoAtual.valor;
    gerenciador->cpu.programa->inteirosAlocados[instrucaoAtual.index] = gerenciador->cpu.programa->inteirosAlocados[instrucaoAtual.index] - instrucaoAtual.valor;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'B':

    gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Bloqueado;
    
    insereNaFila(gerenciador->estadoExec, &gerenciador->estadoBloqueado);

    removidoBloqueado = removeDaFila(&gerenciador->estadoBloqueado);

    insereNaFila(removidoBloqueado, &gerenciador->estadoPronto);

    removidoPronto = removeDaFila(&gerenciador->estadoPronto);

    gerenciador->estadoExec = removidoPronto;

    gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Execucao;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'T':
    
    retiraDaLista(gerenciador->estadoExec, &gerenciador->tabelaProcessos);

    free(gerenciador->cpu.programa);
    free(gerenciador->cpu.vetorMemoria);

    removidoPronto = removeDaFila(&gerenciador->estadoPronto);

    gerenciador->estadoExec = removidoPronto;

    gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Execucao;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    gerenciador->cpu.contadorPrograma++;
    break;
  case 'F':
    novoProcessoSimulado = gerenciador->cpu.programa;

    gerenciador->cpu.programa->ContadorDePrograma += instrucaoAtual.index; //processo pai n instrucoes 

    novoProcessoSimulado->ContadorDePrograma++;

    novoProcesso.processoPaiId = gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processoId;
    novoProcesso.processoId = gerenciador->tabelaProcessos.Ultimo;
    novoProcesso.tempoInicio = gerenciador->tempoCPU;
    novoProcesso.tempoCpu = 0;
    novoProcesso.estados = Pronto;
    novoProcesso.contadorPrograma = &novoProcessoSimulado->ContadorDePrograma;
    novoProcesso.processo = novoProcessoSimulado;
    novoProcesso.prioridade = gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade;

    insereNaLista(novoProcesso, &gerenciador->tabelaProcessos);

    insereNaFila(gerenciador->tabelaProcessos.Ultimo, &gerenciador->estadoPronto);

    gerenciador->tempoCPU++;
    gerenciador->quantidadeProcesos++;
    break;
  case 'R':

    //inicializamos novo processo com o mesmo arquivo
    inicializaProcessoSimulado(instrucaoAtual.nomeArquivo, &novoProcessoSimulado);

    gerenciador->cpu.contadorPrograma = 0;

    free(gerenciador->cpu.vetorMemoria);

    gerenciador->cpu.programa = novoProcessoSimulado;
    //desalocar veto de memoria e adicionar novo procssos

    gerenciador->tempoCPU++;
    break;
  default:
    break;
  }

}

void executaProcessoImpressao(GerenciadorProcessos gerenciador, int imprimeTempoMedio) {
  double tempo;
  
  imprimeCPU(gerenciador.cpu);
  imprimeLista(gerenciador.tabelaProcessos);

  if(imprimeTempoMedio) {
    tempo = gerenciador.tempoCPU / gerenciador.quantidadeProcesos;

    printf("Tempo medio do ciclo: %.2lf\n\n", tempo);
  }
}
