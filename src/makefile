OBJS = main.o game.o input.o screen.o
CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -std=c89 -c
LFLAGS = -lncurses

gol: $(OBJS)
	$(CC) $(OBJS) -o gol $(LFLAGS) -fopenmp

main.o: main.c color.h game.h input.h screen.h
	$(CC) $(CFLAGS) main.c -o main.o -fopenmp

game.o: game.c game.h screen.h
	$(CC) $(CFLAGS) game.c -o game.o

input.o: input.c input.h screen.h
	$(CC) $(CFLAGS) input.c -o input.o

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) screen.c -o screen.o

all: gol

clean:
	rm gol || true
	rm *.o || true
