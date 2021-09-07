#include "Headers/tabelaDeProcessos.h"
#include "Headers/fila.h"

int main (int argc, char *argv[]) {
	// TipoLista lista;

	// inicializaListaVazia(&lista);

	// Insere(10, &lista);
	// Insere(11, &lista);
	// Insere(12, &lista);

	// Imprime(lista);

	// printf("\n");

	// Retira(1, &lista);

	// Imprime(lista);
	
	TipoFila fila;

	iniciaFilaVazia(&fila);

	insereNaFila(10, &fila);
	insereNaFila(11, &fila);
	insereNaFila(12, &fila);

	imprimeFila(fila);

	printf("\n");

	removeDaFila(&fila);

	imprimeFila(fila);
}