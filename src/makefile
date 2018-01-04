OBJS = main.o color.o input.o screen.o
CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -std=c89 -c
LFLAGS = -lncurses

gol: $(OBJS)
	$(CC) $(OBJS) -o gol $(LFLAGS)

main.o: main.c color.h input.h screen.h
	$(CC) $(CFLAGS) main.c -o main.o

color.o: color.c color.h
	$(CC) $(CFLAGS) color.c -o color.o

input.o: input.c input.h screen.h
	$(CC) $(CFLAGS) input.c -o input.o

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) screen.c -o screen.o

all: gol

clean:
	rm gol || true
	rm *.o || true
