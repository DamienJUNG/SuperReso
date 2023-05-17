#include "appareil.h"
#include "routeur.h"
#include "station.h"
#include "graphe.h"

#define ROUTEUR 2
#define STATION 1

typedef struct LAN
{
	routeur *routeurs;
	station *stations;
	graphe g;
	appareil *appareils;
};
