all: projet no_cycle

LAN.o:LAN.c LAN.h
	gcc -c LAN.c

graphe.o:graphe.c graphe.h
	gcc -c graphe.c

devices.o:devices.c devices.h
	gcc -c devices.c

projet:main.c LAN.o graphe.o devices.o
	gcc -Wall -o projet main.c LAN.o graphe.o devices.o

no_cycle:scenario_no_cycle_dialogue.c LAN.o graphe.o devices.o
	gcc -Wall -o no_cycle scenario_no_cycle_dialogue.c LAN.o graphe.o devices.o