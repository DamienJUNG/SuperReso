all: main

LAN.o:LAN.c LAN.h
	gcc -c LAN.c commutateur.c

commutateur.o:commutateur.c commutateur.h
	gcc -c commutateur.c

station.o:station.c station.h
	gcc -c station.c

main:main.c LAN.o commutateur.o station.o
	gcc -Wall -o main main.c LAN.o commutateur.o station.o