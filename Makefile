#Nome do programa
TARGET = app

#diretorios dos arquivos
SRC = ./src
OBJ = ./obj
BIN = ./bin

#compilador
CC = gcc

OBJS =	main.o header.o

all: $(OBJS)
	$(CC) $(OBJ)/*.o -o $(BIN)/$(TARGET)

header.o: $(SRC)/header.c
	$(CC) -c $(SRC)/header.c -o $(OBJ)/header.o

main.o: $(SRC)/main.c
	$(CC) -c $(SRC)/main.c -o $(OBJ)/main.o

run:
	$(BIN)/$(TARGET)

clean:
	rm $(OBJ)/*.o
	rm $(BIN)/*