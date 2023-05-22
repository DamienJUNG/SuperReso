all: main

LAN.o:LAN.c LAN.h
	gcc -c LAN.c

main:main.c LAN.o
	gcc -Wall -o main main.c LAN.o