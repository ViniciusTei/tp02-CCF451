#include "headers/executaProcesso.h"

void executaProximaInstrucaoProcessoSimulado(GerenciadorProcessos *gerenciador) {
  Instrucao instrucaoAtual = gerenciador->cpu.programa->instrucoesPrograma[gerenciador->cpu.programa->ContadorDePrograma];

//   switch (instrucaoAtual.instrucao)
//   {
//   case 'N':
//     /* code */
    
//     gerenciador->cpu.programa->QntdInteiros =  instrucaoAtual.index;

//     gerenciador->cpu.programa->ContadorDePrograma++;
//     gerenciador->cpu.unidadesTempoUsadas++;
//     gerenciador->tempoCPU++;
//     break;
//   case 'D':
//     int tamanho = instrucaoAtual.index + 1; 

//     if(gerenciador->cpu.vetorMemoria == NULL) {
//       gerenciador->cpu.vetorMemoria = (int *) malloc(sizeof(int) * tamanho);
//     } else {
//       gerenciador->cpu.vetorMemoria = (int *) realloc(gerenciador->cpu.vetorMemoria, sizeof(int) * tamanho);

//     }

//     gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = 0;

//     gerenciador->cpu.programa->ContadorDePrograma++;
//     gerenciador->cpu.unidadesTempoUsadas++;
//     gerenciador->tempoCPU++;
//     break;
//   case 'V':
//     gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = instrucaoAtual.valor;

//     gerenciador->cpu.programa->ContadorDePrograma++;
//     gerenciador->cpu.unidadesTempoUsadas++;
//     gerenciador->tempoCPU++;
//     break;
//   case 'A':
//     gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = gerenciador->cpu.vetorMemoria[instrucaoAtual.index] + instrucaoAtual.valor;

//     gerenciador->cpu.programa->ContadorDePrograma++;
//     gerenciador->cpu.unidadesTempoUsadas++;
//     gerenciador->tempoCPU++;
//     break;
//   case 'S':
//     gerenciador->cpu.vetorMemoria[instrucaoAtual.index] = gerenciador->cpu.vetorMemoria[instrucaoAtual.index] - instrucaoAtual.valor;

//     gerenciador->cpu.programa->ContadorDePrograma++;
//     gerenciador->cpu.unidadesTempoUsadas++;
//     gerenciador->tempoCPU++;
//     break;
//   case 'B':

//     gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Bloqueado;
    
//     insereNaFila(gerenciador->estadoExec, &gerenciador->estadoBloqueado);

//     int removidoBloqueado = removeDaFila(&gerenciador->estadoBloqueado);

//     insereNaFila(removidoBloqueado, &gerenciador->estadoPronto);

//     int removidoPronto = removeDaFila(&gerenciador->estadoPronto);

//     gerenciador->estadoExec = removidoPronto;

//     gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Execucao;

//     gerenciador->cpu.programa->ContadorDePrograma++;
//     gerenciador->cpu.unidadesTempoUsadas++;
//     gerenciador->tempoCPU++;
//     break;
//   case 'T':
    
//     retiraDaLista(gerenciador->estadoExec, &gerenciador->tabelaProcessos);

//     free(gerenciador->cpu.programa);
//     free(gerenciador->cpu.vetorMemoria);

//     int removidoPronto = removeDaFila(&gerenciador->estadoPronto);

//     gerenciador->estadoExec = removidoPronto;

//     gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].estados = Execucao;

//     gerenciador->cpu.programa->ContadorDePrograma++;
//     gerenciador->cpu.unidadesTempoUsadas++;
//     gerenciador->tempoCPU++;
//     break;
//   case 'F':
//     ProcessoSimulado novoProcessoSimulado = *gerenciador->cpu.programa;
//     Processo novoProcesso;

//     gerenciador->cpu.programa->ContadorDePrograma += instrucaoAtual.index; //processo pai n instrucoes 

//     novoProcessoSimulado.ContadorDePrograma++;

//     novoProcesso.processoPaiId = gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].processoId;
//     novoProcesso.processoId = gerenciador->tabelaProcessos.Ultimo;
//     novoProcesso.tempoInicio = gerenciador->tempoCPU;
//     novoProcesso.tempoCpu = 0;
//     novoProcesso.estados = Pronto;
//     novoProcesso.contadorPrograma = &novoProcessoSimulado.ContadorDePrograma;
//     novoProcesso.processo = &novoProcessoSimulado;
//     novoProcesso.prioridade = gerenciador->tabelaProcessos.Item[gerenciador->estadoExec].prioridade;

//     insereNaLista(novoProcesso, &gerenciador->tabelaProcessos);

//     insereNaFila(gerenciador->tabelaProcessos.Ultimo, &gerenciador->estadoPronto);

//     gerenciador->tempoCPU++;
//     break;
//   case 'R':
//     ProcessoSimulado novoProcessoSimulado;

//     inicializaProcessoSimulado(instrucaoAtual.nomeArquivo, &novoProcessoSimulado);

//     gerenciador->cpu.contadorPrograma = 0;

//     //desalocar veto de memoria e adicionar novo procssos

//     break;
//   default:
//     break;
//   }

}
