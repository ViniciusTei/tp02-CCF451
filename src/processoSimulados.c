#include "headers/processoSimulados.h"

void inicializaProcessoSimulado(char* nomeArquivo, ProcessoSimulado *processo) {
    //inicializar o primeiro processo simulado
    int inteiros;
    int qtdLinhas = inicializaInstrucoes(nomeArquivo, processo->instrucoesPrograma, &inteiros);
    processo->QtdInstrucoes = qtdLinhas;
    processo->QntdInteiros = inteiros;
    processo->ContadorDePrograma = 0;
  
}

int inicializaInstrucoes(char* nomeArquivo, Instrucao* instrucoes, int *qtdInteiros){
  int qtdLinhas, cont, valor,index;
  FILE *arq;
  char nomeArquivoNovo[100];
  char instrucao;
  char numeros[100];
  qtdLinhas = contadorInstrucoes(nomeArquivo);
  //printf("\nQtdLinhas: %d\n", qtdLinhas);
  //aloca o numero exato de instrucoes
  instrucoes = malloc(qtdLinhas * sizeof (Instrucao));
  //Abre arquivo
  arq = fopen(nomeArquivo,"rt");
  //adicionar instrucoes no vetor;
  for(cont = 0; cont<qtdLinhas;cont++){
    //Pega linha
    //dixava linha
    fscanf(arq, "%c", &instrucao);
    instrucoes[cont].instrucao = instrucao;
    if((instrucoes[cont].instrucao == 'B')||(instrucoes[cont].instrucao == 'T')){
      //termina
    }else if(((instrucoes[cont].instrucao == 'N')||(instrucoes[cont].instrucao == 'D')||(instrucoes[cont].instrucao == 'F'))
    ||(instrucoes[cont].instrucao == 'R')||(instrucoes[cont].instrucao == 'S')||(instrucoes[cont].instrucao == 'A')||(instrucoes[cont].instrucao == 'V')){
      if((instrucoes[cont].instrucao == 'N')||(instrucoes[cont].instrucao == 'D')||(instrucoes[cont].instrucao == 'F')){
        fscanf(arq, "%d", &index);
        instrucoes[cont].index = index;

        if(cont == 0 && instrucoes[cont].instrucao == 'N') {
          *qtdInteiros = index;
        }

      }else if(instrucoes[cont].instrucao == 'R'){ // R
        fscanf(arq, "%s", nomeArquivoNovo);
        strcpy(instrucoes[cont].nomeArquivo,nomeArquivoNovo);
      }else{
        fscanf(arq, "%d" "%d", &index, &valor);
        instrucoes[cont].index = index;
        instrucoes[cont].valor = valor;
      }
    }else{
      cont--; // como o primeiro caracter era espaço temos que voltar o contador, sempre que nao pegar nenhum caracter
    }
  }
  
  printf("\nInstrução carregada\n");
  //fecha arquivo
  fclose(arq);
  return qtdLinhas;
}

int contadorInstrucoes(char* nomeArquivo){
  //declaração de variaveis
  FILE *arq;
  int contLinhas;
  char letra;
  contLinhas = 0;
  //inicia arquivo
   arq = fopen(nomeArquivo,"rt");
  //Loop para percorrer o arquivo e pegar a quantidade de linhas
  while( (letra=fgetc(arq)) != EOF) {
    if (letra=='\n') contLinhas++;
  }
  //printf("\nNumero Linhas: %d", contLinhas);
  //fecha arquivo
  fclose(arq);
  return contLinhas;
}

void executaProximaInstrucaoProcessoSimulado(GerenciadorProcessos *gerenciador) {
  Instrucao instrucaoAtual = gerenciador->cpu.programa->instrucoesPrograma[gerenciador->cpu.programa->ContadorDePrograma];

  switch (instrucaoAtual.instrucao)
  {
  case 'N':
    /* code */
    
    gerenciador->cpu.programa->QntdInteiros =  instrucaoAtual.index;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    break;
  case 'D':
    int tamanho = instrucaoAtual.index + 1; 

    if(gerenciador->cpu.vetorMemoria == NULL) {
      gerenciador->cpu.vetorMemoria = (int *) malloc(sizeof(int) * tamanho);
    } else {
      gerenciador->cpu.vetorMemoria = (int *) realloc(gerenciador->cpu.vetorMemoria, sizeof(int) * tamanho);

    }

    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = 0;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    break;
  case 'V':
    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = instrucaoAtual.valor;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    break;
  case 'A':
    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = gerenciador->cpu.vetorMemoria[instrucaoAtual.index] + instrucaoAtual.valor;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    break;
  case 'S':
    gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = gerenciador->cpu.vetorMemoria[instrucaoAtual.index] - instrucaoAtual.valor;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    break;
  case 'B':

    gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Bloqueado;
    
    insereNaFila(gerenciador->estadoExec, &gerenciador->estadoBloqueado);

    int removidoBloqueado = removeDaFila(&gerenciador->estadoBloqueado);

    insereNaFila(removidoBloqueado, &gerenciador->estadoPronto);

    int removidoPronto = removeDaFila(&gerenciador->estadoPronto);

    gerenciador->estadoExec = removidoPronto;

    gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Execucao;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    break;
  case 'T':
    
    retiraDaLista(gerenciador->estadoExec, &gerenciador->tabelaProcessos);

    free(gerenciador->cpu.programa);
    free(gerenciador->cpu.vetorMemoria);

    int removidoPronto = removeDaFila(&gerenciador->estadoPronto);

    gerenciador->estadoExec = removidoPronto;

    gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Execucao;

    gerenciador->cpu.programa->ContadorDePrograma++;
    gerenciador->cpu.unidadesTempoUsadas++;
    gerenciador->tempoCPU++;
    break;
  case 'F':
    ProcessoSimulado novoProcessoSimulado = *gerenciador->cpu.programa;
    Processo novoProcesso;

    gerenciador->cpu.programa->ContadorDePrograma += instrucaoAtual.index; //processo pai n instrucoes 

    novoProcessoSimulado.ContadorDePrograma++;

    novoProcesso.processoPaiId = gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processoId;
    novoProcesso.processoId = gerenciador->tabelaProcessos.Ultimo;
    novoProcesso.tempoInicio = gerenciador->tempoCPU;
    novoProcesso.tempoCpu = 0;
    novoProcesso.estados = Pronto;
    novoProcesso.contadorPrograma = &novoProcessoSimulado.ContadorDePrograma;
    novoProcesso.processo = &novoProcessoSimulado;
    novoProcesso.prioridade = gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade;

    insereNaLista(novoProcesso, &gerenciador->tabelaProcessos);

    insereNaFila(gerenciador->tabelaProcessos.Ultimo, &gerenciador->estadoPronto);

    gerenciador->tempoCPU++;
    break;
  case 'R':
    ProcessoSimulado novoProcessoSimulado;

    inicializaProcessoSimulado(instrucaoAtual.nomeArquivo, &novoProcessoSimulado);

    gerenciador->cpu.contadorPrograma = 0;

    //desalocar veto de memoria e adicionar novo procssos

    break;
  default:
    break;
  }

}
