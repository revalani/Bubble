CC=gcc

#CFLAGS=-g -pedantic -lm -w -ansi -Wall -D_GNU_SOURCE=1 -D_REENTRANT
CFLAGS=-lm -w
SFLAGS=-lSDL2 -lSDL2main
LIBs_FLAGS=-lSDL2_image -lSDL2_mixer -lSDL2_ttf

SOURCES=./script/main.c 
ARQAUX=./script/gamefunctions.c ./script/globais.c ./script/initfunctions.c
BINARIES=Bubble

#all: ex0 ex1 ex2 ex3 ex4 ex5 ex6 ex7 grafico texto
all: $(BINARIES)

Bubble: ./script/main.c
	$(CC) -o $(BINARIES) $(SOURCES) $(ARQAUX) $(CFLAGS) $(SFLAGS) $(LIBs_FLAGS) 

clean:
	rm -rf *.o *.exe *.bak *.c~ $(BINARIES) core a.out

#gcc script/main.c ./script/gamefunctions.c ./script/globais.c ./script/initfunctions.c -o p -w -lm -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
