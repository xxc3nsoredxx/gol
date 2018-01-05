BIN = bin
SRC = src
OBJS = $(BIN)/main.o $(BIN)/game.o $(BIN)/input.o $(BIN)/screen.o
CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -std=c89 -c
LFLAGS = -lncurses

$(BIN)/gol: $(OBJS)
	$(CC) $(OBJS) -o $(BIN)/gol $(LFLAGS) -fopenmp

$(BIN)/main.o: $(SRC)/main.c $(SRC)/color.h $(SRC)/game.h \
               $(SRC)/input.h $(SRC)/screen.h
	$(CC) $(CFLAGS) $(SRC)/main.c -o $(BIN)/main.o -fopenmp

$(BIN)/game.o: $(SRC)/game.c $(SRC)/game.h $(SRC)/screen.h
	$(CC) $(CFLAGS) $(SRC)/game.c -o $(BIN)/game.o

$(BIN)/input.o: $(SRC)/input.c $(SRC)/input.h $(SRC)/screen.h
	$(CC) $(CFLAGS) $(SRC)/input.c -o $(BIN)/input.o

$(BIN)/screen.o: $(SRC)/screen.c $(SRC)/screen.h
	$(CC) $(CFLAGS) $(SRC)/screen.c -o $(BIN)/screen.o

all: $(BIN)/gol

clean:
	rm $(BIN)/gol || true
	rm $(BIN)/*.o || true
