#include "headers/processoControle.h"

void iniciaProcessoControle () {
    int i;
    pid_t pid;
    int fd[2], fd_filho[2];
    char stringEntrada[256];
    char stringRecebida[256];
    
    if(pipe(fd) < 0) {
        perror("pipe error");
        exit(1);
    }

    /*     if(pipe(fd_filho) < 0) {
            perror("pipe error");
            exit(1);
        } */

    if((pid = fork())<0){
        perror("fork error");
        exit(1);
    }

    if(pid > 0) { //processo pai

        close(fd[0]);

        //pede do usuario qual o tipo de entrada arquivo ou terminal
        int entradaUsuario;
        do {
            sleep(1);
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
        write(fd[1], stringEntrada, sizeof(stringEntrada) + 1);
        //close(fd[1]);
        exit(0);

        return 1;
    } 
    else { //processo filho       
        GerenciadorProcessos gerenciador;
        //ProcessoSimulado primeiroProcessoSimulado;
        Processo pprocesso;
        
        if(pipe(fd_filho) < 0) {
            perror("pipe error");
            exit(1);
        }

        //inicia processo gerenciador de processos
        iniciaGerenciadorProcessos(&gerenciador);

        inicializaProcessoSimulado("./Arquivos/init.txt", &gerenciador.cpu.programa);

        pprocesso.processoId = gerenciador.tabelaProcessos.Ultimo;
        pprocesso.processoPaiId = getpid();
        pprocesso.contadorPrograma = &gerenciador.cpu.programa->ContadorDePrograma;
        pprocesso.processo = &gerenciador.cpu.programa;
        pprocesso.estados = Pronto;
        pprocesso.tempoInicio = gerenciador.tempoCPU;
        pprocesso.tempoCpu = 0;
        pprocesso.prioridade = 0;

        insereNaLista(pprocesso, &gerenciador.tabelaProcessos); //insere processo na tabela de processos

        //insereNaFila(0, &gerenciador.estadoPronto);

        close(fd[1]);
        read(fd[0], stringRecebida, sizeof(stringRecebida));
        //close(fd[0]);
        printf("String recebida: %s | PID: %i\n", stringRecebida, getpid());

        //executa a partir da entrada

        for(int i = 0 ; i < sizeof(stringRecebida); i++){

            if(stringRecebida[i] == 'M') {
                printf("exec %c\n", stringRecebida[i]);
                break;
            } else if (stringRecebida[i] == 'U') {
                printf("exec %c\n", stringRecebida[i]);

                executaProximaInstrucaoProcessoSimulado(&gerenciador);
                //atualizar o q for necessario



            }
        }
        
        return 0;
    }
}

void lerArquivo(char* retorno){ 
    FILE *arquivo;
    char str[2];

    arquivo = fopen("./Arquivos/Controle.txt", "r");
    
    if( arquivo == NULL){
      printf("Erro ao abrir arquivo\n");
      return NULL;
    }
    else{
      while( fscanf(arquivo, "%s", str) != EOF ){
        strcat(retorno,str);
        strcat(retorno," ");
      }

      fclose(arquivo);
    }
    
}

void lerTerminal(char* retorno){
    char comando;
    int i = 0;
    
    printf("Entre com os comandos:\n");
    
    do {
        scanf("%c",&comando);
        retorno[i] = comando;
        strcat(retorno, " ");
        i++;
    } while(comando != 'M');

     remove_char(retorno, '\n');
    
}

//função para remover o \n
void remove_char(char* str, char c) {
    char *pr= str, *pw = str;

    while(*pr)
    {
        *pw = *pr++;
        pw += (*pw != c);
    }

    *pw = '\0';
}