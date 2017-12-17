OBJS = main.o color.o screen.o
CC = gcc
CFLAGS = -Wall -Wextra -c

gol: $(OBJS)
	$(CC) $(OBJS) -o gol

main.o: main.c color.h screen.h
	$(CC) $(CFLAGS) main.c -o main.o

color.o: color.c color.h
	$(CC) $(CFLAGS) color.c -o color.o

screen.o: screen.c screen.h
	$(CC) $(CFLAGS) screen.c -o screen.o
