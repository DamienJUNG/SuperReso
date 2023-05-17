#include "appareil.h"
#include "routeur.h"
#include "station.h"
#include "graphe.h"
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
	graphe g;
	appareil *appareils;
};

void recupere_config(LAN *lan, char* filename);
void ajoute_routeur(LAN *lan,routeur rout);
void ajoute_station(LAN *lan,station stat);
