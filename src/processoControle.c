#include "headers/processoControle.h"

/*
 * Function:  iniciaProcessoControle 
 * 
 * Inicia um processo pai que vai receber as entradas do usuario
 * e um processo filho que vai processar essas entradas.
 *
 * @params:
 *
 *  returns: void
 */
void iniciaProcessoControle () {
    int i;
    pid_t pid;
    int fd[2], fd_filho[2];
    char stringEntrada[100];
    char stringRecebida[100];

    GerenciadorProcessos gerenciador;
    ProcessoSimulado primeiroProcessoSimulado;
    Processo pprocesso;
    TipoItem x;

    int removidoBloquado, removidoPronto;
    
    if(pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }

    if((pid = fork())<0){
        perror("fork error");
        exit(1);
    }

    if(pid > 0) { //processo pai

        close(fd[0]);

        //pede do usuario qual o tipo de entrada arquivo ou terminal
        int entradaUsuario;
        do {
            sleep(2);
            printf("Deseja ler a entrada de um arquivo ou terminal?\n");
            printf("1. Terminal\n");
            printf("2. Arquivo\n");
            printf("Entre com um valor: ");
            scanf("%d", &entradaUsuario);

            if(entradaUsuario == 1 || entradaUsuario == 2) {
                //get Entrada
                if(entradaUsuario == 1){
                    lerTerminal(stringEntrada);
                    break;
                }else{
                    lerArquivo(stringEntrada);
                    break;
                }
                
                
            } else {
                printf("Entrada invalida!\n\n");
            }
        } while(entradaUsuario != 1 || entradaUsuario != 2);

        printf("String enviada: %s\n", stringEntrada);

        //escreve no pipe
        write(fd[1], stringEntrada, sizeof(stringEntrada)+2);
        //close(fd[1]);
        exit(0);

        return ;
    } 
    else { //processo filho       
       
        
        if(pipe(fd_filho) < 0) {
            perror("pipe error");
            exit(1);
        }

        //inicia processo gerenciador de processos
        iniciaGerenciadorProcessos(&gerenciador);
        primeiroProcessoSimulado = inicializaProcessoSimulado("./Arquivos/test.txt");

        gerenciador.quantidadeProcesos++;
        pprocesso.processoId = gerenciador.tabelaProcessos.Ultimo;
        pprocesso.processoPaiId = getpid();
        pprocesso.contadorPrograma = primeiroProcessoSimulado.ContadorDePrograma;
        pprocesso.estados = Pronto;
        pprocesso.tempoInicio = gerenciador.tempoAtual;
        pprocesso.tempoCpu = 0;
        pprocesso.prioridade = primeiroProcessoSimulado.prioridade;
        
        pprocesso.processo.processoId = primeiroProcessoSimulado.processoId;
        pprocesso.processo.ContadorDePrograma = primeiroProcessoSimulado.ContadorDePrograma;
        pprocesso.processo.prioridade = primeiroProcessoSimulado.prioridade;
        pprocesso.processo.QntdInteiros = primeiroProcessoSimulado.QntdInteiros;
        pprocesso.processo.QtdInstrucoes = primeiroProcessoSimulado.QtdInstrucoes;

        pprocesso.processo.instrucoesPrograma = (Instrucao *) malloc(sizeof(Instrucao) * pprocesso.processo.QtdInstrucoes);

        for(int i = 0; i < pprocesso.processo.QtdInstrucoes; i++) {
            pprocesso.processo.instrucoesPrograma[i].index = primeiroProcessoSimulado.instrucoesPrograma[i].index;
            pprocesso.processo.instrucoesPrograma[i].instrucao = primeiroProcessoSimulado.instrucoesPrograma[i].instrucao;
            pprocesso.processo.instrucoesPrograma[i].valor = primeiroProcessoSimulado.instrucoesPrograma[i].valor;
            strcpy(pprocesso.processo.instrucoesPrograma[i].nomeArquivo, primeiroProcessoSimulado.instrucoesPrograma[i].nomeArquivo);
        }

        insereNaLista(pprocesso, &gerenciador.tabelaProcessos); //insere processo na tabela de processos

        //gerenciador.cpu.processoAtual = &pprocesso;
        
        x.indeceTabelaProcessos = pprocesso.processoId;
        x.prioridade = &pprocesso.prioridade;

        insereNaFila(x, &gerenciador.estadoPronto);
        imprimeFila(gerenciador.estadoPronto);
        
        gerenciador.estadoExec = removeDaFila(&gerenciador.estadoPronto);        
        gerenciador.tabelaProcessos.Item[gerenciador.estadoExec].estados = Execucao;

        iniciaCPU(&gerenciador, primeiroProcessoSimulado);       
        gerenciador.cpu.processoAtual = &gerenciador.tabelaProcessos.Item[gerenciador.estadoExec];

        close(fd[1]);
        read(fd[0], stringRecebida, sizeof(stringRecebida));
        //close(fd[0]);
        printf("String recebida: %s | PID: %i\n", stringRecebida, getpid());

        //executa a partir da entrada

        for(int i = 0 ; i < sizeof(stringRecebida); i++){

            if(stringRecebida[i] == 'M') {
                executaProcessoImpressao(gerenciador, TRUE);

                //finaliza execucao
                exit(0);
                return;
            } else if (stringRecebida[i] == 'U') {
                controleEscalonamento(&gerenciador);
                //atualizar o q for necessario

            } else if(stringRecebida[i] == 'L') {
                removidoBloquado = removeDaFila(&gerenciador.estadoBloqueado);

                if(removidoBloquado > -1) {
                    x.indeceTabelaProcessos = removidoBloquado;
                    x.prioridade = &gerenciador.tabelaProcessos.Item[removidoBloquado].prioridade;

                    insereNaFila(x, &gerenciador.estadoPronto);
                } else {
                    printf("Nao existem processos para desbloquear!\n");
                }

                
            } else if(stringRecebida[i] == 'I') {
                //processo impressao
                executaProcessoImpressao(gerenciador, FALSE);
            }
        }
        exit(0);
        return ;
    }
}

/*
 * Function:  lerArquivo 
 * 
 * Pega a entrada a partir do arquivo de controle
 *
 * @params:
 * retorno: string lida do arquivo
 *
 *  returns: void
 */
void lerArquivo(char* retorno){ 
    FILE *arquivo;
    char str[2];

    arquivo = fopen("./Arquivos/Controle.txt", "r");
    
    if( arquivo == NULL){
      printf("Erro ao abrir arquivo\n");
      return ;
    }
    else{
      while( fscanf(arquivo, "%s", str) != EOF ){
        strcat(retorno,str);
        strcat(retorno," ");
      }

      fclose(arquivo);
    }
    
}

/*
 * Function:  lerTerminal 
 * 
 * Pega a entrada a partir do terminal do usuario
 *
 * @params:
 * retorno: string lida do terminal
 *
 *  returns: void
 */
void lerTerminal(char* retorno){
    char comando;
    int i = 0;
    
    printf("Entre com os comandos:\n");
    
    do {
        scanf("%c",&comando);
        if(comando>=97 && comando<=120){
            comando=comando-32;
        }
        retorno[i] = comando;
        strcat(retorno, " ");
        i++;
    } while(comando != 'M');

     remove_char(retorno, '\n');
    
}

/*
 * Function:  remove_char 
 * 
 * Funcao auxiliar que remove um char de uma string
 *
 * @params:
 * str: string que queremos trabalhar
 * c: char que queremos remover da string
 *
 *  returns: void
 */
void remove_char(char* str, char c) {
    char *pr= str, *pw = str;

    while(*pr)
    {
        *pw = *pr++;
        pw += (*pw != c);
    }

    *pw = '\0';
}