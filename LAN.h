#include "appareil.h"
#include "commutateur.h"
#include "station.h"
//#include "graphe.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMUTATEUR 2
#define STATION 1

typedef struct LAN
{
	commutateur *commutateurs;
	station *stations;
	unsigned int nb_commutateur;
	unsigned int nb_station;
	unsigned int curs_commutateur;
	unsigned int curs_station;
	//graphe graphe;
	appareil *appareils;
}LAN;
void init_Lan(LAN *lan);
void free_Lan(LAN *lan);
void recupere_config(LAN *lan, const char* filename);
void ajoute_commutateur(LAN *lan,commutateur rout);
void ajoute_station(LAN *lan,station stat);
unsigned char* construit_mac(char* token);
