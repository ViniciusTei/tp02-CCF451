#include "headers/processoSimulados.h"

void inicializaProcessoSimulado(char* nomeArquivo, ProcessoSimulado **processo) {
    //inicializar o primeiro processo simulado
    *processo = (ProcessoSimulado* ) malloc(sizeof(ProcessoSimulado));

    int inteiros = 0, qtdLinhas = 0;
    qtdLinhas = inicializaInstrucoes(nomeArquivo, &(*processo)->instrucoesPrograma, &inteiros);
    (*processo)->inteirosAlocados = NULL;
    (*processo)->QtdInstrucoes = qtdLinhas;
    (*processo)->QntdInteiros = inteiros;
    (*processo)->ContadorDePrograma = 0;
  
}

int inicializaInstrucoes(char* nomeArquivo, Instrucao** instrucoes, int *qtdInteiros){
  int qtdLinhas, cont, valor,index;
  FILE *arq;
  char nomeArquivoNovo[100];
  char instrucao;
  char numeros[100];
  qtdLinhas = contadorInstrucoes(nomeArquivo);
  //printf("\nQtdLinhas: %d\n", qtdLinhas);
  //aloca o numero exato de instrucoes
  *instrucoes = malloc(qtdLinhas * sizeof (Instrucao));
  //Abre arquivo
  arq = fopen(nomeArquivo,"rt");
  //adicionar instrucoes no vetor;
  for(cont = 0; cont<qtdLinhas;cont++){
    //Pega linha
    //dixava linha
    fscanf(arq, "%c", &instrucao);
    (*instrucoes)[cont].instrucao = instrucao;
    if(((*instrucoes)[cont].instrucao == 'B') || ((*instrucoes)[cont].instrucao == 'T')){
      //termina
    }else if((((*instrucoes)[cont].instrucao == 'N') || ((*instrucoes)[cont].instrucao == 'D') || ((*instrucoes)[cont].instrucao == 'F'))
     || ((*instrucoes)[cont].instrucao == 'R') || ((*instrucoes)[cont].instrucao == 'S') || ((*instrucoes)[cont].instrucao == 'A') || ((*instrucoes)[cont].instrucao == 'V')){
      if(((*instrucoes)[cont].instrucao == 'N') || ((*instrucoes)[cont].instrucao == 'D') || ((*instrucoes)[cont].instrucao == 'F')){
        fscanf(arq, "%d", &index);
        (*instrucoes)[cont].index = index;

        if(cont == 0 && (*instrucoes)[cont].instrucao == 'N') {
          *qtdInteiros = index;
        }

      }else if((*instrucoes)[cont].instrucao == 'R'){ // R
        fscanf(arq, "%s", nomeArquivoNovo);
        strcpy((*instrucoes)[cont].nomeArquivo,nomeArquivoNovo);
      }else{
        fscanf(arq, "%d" "%d", &index, &valor);
        (*instrucoes)[cont].index = index;
        (*instrucoes)[cont].valor = valor;
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

void imprimeProcessoSimulado(ProcessoSimulado processo) {
  printf("Processo simulado\n");
}