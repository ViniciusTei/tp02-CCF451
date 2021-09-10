#ifndef PROCESSO_CONTROLE
#define PROCESSO_CONTROLE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <ctype.h>
#include "gerenciadorProcessos.h"
#include "processoSimulados.h"

// typedef enum Comandos {
//     U, L, I, M
// } Comandos;

void iniciaProcessoControle ();
void lerArquivo(char* retorno);
void lerTerminal(char* retorno);
void remove_char(char* str, char c);

#endif