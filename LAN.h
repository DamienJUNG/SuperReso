#include "appareil.h"
#include "commutateur.h"
#include "commutation.h"
#include "station.h"
#include "graphe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMUTATEUR 2
#define STATION 1

typedef struct station
{
	unsigned char mac[6];
	unsigned char ip[4];
}station;

typedef struct commutateur {
	unsigned char mac[6];
	unsigned int nb_ports;
	unsigned int priorite;
	commutation table[64];//table de commutation
}commutateur;


typedef struct LAN
{
	commutateur *commutateurs;
	station *stations;
	unsigned int commutateur_capacite;
	unsigned int station_capacite;
	unsigned int nb_commutateur;
	unsigned int nb_station;
	graphe graphe;
	appareil *appareils;
}LAN;
void init_Lan(LAN *lan);
void free_Lan(LAN *lan);
void recupere_config(LAN *lan, const char* filename);
void ajoute_commutateur(LAN *lan,commutateur comm);
void ajoute_station(LAN *lan,station stat);
void construit_mac(char* token,unsigned char* mac);
unsigned int converti_champ(char* champ);
int puissance(int nb, int expo);
void construit_ip(char* token, unsigned char* ip);
void show_devices(LAN *lan);
void print_mac(unsigned char* mac);
void print_ip(unsigned char* mac);

