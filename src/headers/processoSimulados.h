typedef char Instrucao[20]; //Armazena uma instrução

typedef struct Programa{
  Instrucao instrucoes[20]; //Armazena instruções de um programa
  int QtdInstrucoes; //Qtd de instruções do programa;
  int Frente,Tras; //Fila de programas
} Programa;

typedef struct ProcessoSimulado{
  int QntdInteiros;
  int Alocado_V_inteiros;
  int *Inteiro; //quantidade de inteiros do processo pai
  int ContadorDePrograma;
  int QtdInstrucoes;
  Instrucao Programa[20];
} ProcessoSimulado;