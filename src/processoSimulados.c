#include "headers/processoSimulados.h"

/*
 * Function:  inicializaProcessoSimulado 
 * 
 * Cria e inicializa uma estrutura de um processo simulado.
 * Lemos um arquivo com essa estrutura e salvamos em uma 
 * variavel na memoria.
 *
 * @params:
 * nomeArquivo: nome do arquivo com o processo simulado
 *
 *  returns: ProcessoSimulado 
 */
ProcessoSimulado inicializaProcessoSimulado(char* nomeArquivo) {
    //inicializar o primeiro processo simulado
    ProcessoSimulado *processo;
    processo = (ProcessoSimulado* ) malloc(sizeof(ProcessoSimulado));

    int inteiros = 0, qtdLinhas = 0;
    qtdLinhas = inicializaInstrucoes(nomeArquivo, &processo->instrucoesPrograma, &inteiros);
    //
    processo->inteirosAlocados = NULL;
    processo->QtdInstrucoes = qtdLinhas;
    processo->QntdInteiros = inteiros;
    processo->ContadorDePrograma = 0;
    // (*processo)->processoId = rand() % 10000;
    processo->prioridade = 0;

    return *processo;
}

/*
 * Function:  inicializaInstrucoes 
 * 
 * Armazena as instrucoes na estrutura, lendo e 
 * salvando os valores dependendo da instrucao lida.
 *
 * @params:
 * nomeArquivo: nome do arquivo com o processo simulado
 * instrucoes: o ponteiro onde vamos guardas as intrucoes
 * qtdInteiros: o ponteiro onde vamos salvar a quantidade de inteiros
 *
 *  returns: a quantidade de instrucoes que lemos no arquivo 
 */
int inicializaInstrucoes(char* nomeArquivo, Instrucao** instrucoes, int *qtdInteiros){
  int qtdLinhas, cont, valor,index;
  FILE *arq;
  char nomeArquivoNovo[100];
  char instrucao;
  char numeros[100];
  qtdLinhas = _contadorInstrucoes(nomeArquivo);
  //printf("\nQtdLinhas: %d\n", qtdLinhas);
  //aloca o numero exato de instrucoes
  *instrucoes = (Instrucao *) malloc(qtdLinhas * sizeof (Instrucao));
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
  
  //fecha arquivo
  fclose(arq);
  return qtdLinhas;
}

/*
 * Function:  _contadorInstrucoes 
 * 
 * Funcao privada acessada apenas no processo simulado
 * para contar o numero de instrucoes no arquivo.
 *
 * @params:
 * nomeArquivo: nome do arquivo com o processo simulado
 *
 *  returns: a quantidade de instrucoes que lemos no arquivo 
 */
int _contadorInstrucoes(char* nomeArquivo){
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

/*
 * Function:  imprimeProcessoSimulado 
 * 
 * Funcao para imprimir o estado de um processo simulado.
 *
 * @params:
 * processo: processo simulado que vamos trabalhar
 *
 *  returns: void
 */
void imprimeProcessoSimulado(ProcessoSimulado processo) {
  printf("Processo simulado: %d\n", processo.QtdInstrucoes );

  for(int i = 0; i < processo.QtdInstrucoes; i++) {
    printf("Instrucao: %c\n", processo.instrucoesPrograma[i].instrucao);
  }
}