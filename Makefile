#Nome do programa
TARGET = app

#diretorios dos arquivos
SRC = ./src
OBJ = ./obj
BIN = ./bin

#compilador
CC = gcc

OBJS =	main.o tabelaDeProcessos.o fila.o processoControle.o

all: $(OBJS)
	$(CC) $(OBJ)/*.o -o $(BIN)/$(TARGET)

fila.o: $(SRC)/fila.c
	$(CC) -c $(SRC)/fila.c -o $(OBJ)/fila.o

processoControle.o: $(SRC)/processoControle.c
	$(CC) -c $(SRC)/processoControle.c -o $(OBJ)/processoControle.o

tabelaDeProcessos.o: $(SRC)/tabelaDeProcessos.c
	$(CC) -c $(SRC)/tabelaDeProcessos.c -o $(OBJ)/tabelaDeProcessos.o

main.o: $(SRC)/main.c
	$(CC) -c $(SRC)/main.c -o $(OBJ)/main.o

run:
	$(BIN)/$(TARGET)

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*