all: test

LAN.o:LAN.c LAN.h
	gcc -c LAN.c commutateur.c

commutateur.o:commutateur.c commutateur.h
	gcc -c commutateur.c

station.o:station.c station.h
	gcc -c station.c

graphe.o:graphe.c graphe.h
	gcc -c graphe.c

test:main.c LAN.o commutateur.o station.o graphe.o
	gcc -Wall -o test main.c LAN.o commutateur.o station.o graphe.o