#include "appareil.h"
#include "routeur.h"
#include "station.h"
//#include "graphe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROUTEUR 2
#define STATION 1

typedef struct LAN
{
	routeur *routeurs;
	station *stations;
	unsigned int nb_routeur;
	unsigned int nb_station;
	unsigned int curs_routeur;
	unsigned int curs_station;
	//graphe graphe;
	appareil *appareils;
}LAN;
void init_Lan(LAN *lan);
void free_Lan(LAN *lan);
void recupere_config(LAN *lan, const char* filename);
void ajoute_routeur(LAN *lan,routeur rout);
void ajoute_station(LAN *lan,station stat);
unsigned char* construit_mac(char* token);
