all: test

LAN.o:LAN.c LAN.h
	gcc -c LAN.c

graphe.o:graphe.c graphe.h
	gcc -c graphe.c

frame.o:frame.c frame.h
	gcc -c frame.c

test:main.c LAN.o graphe.o frame.o
	gcc -Wall -o test main.c LAN.o graphe.o frame.o