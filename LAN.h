#include "graphe.h"
#include "devices.h"

#define BRIDGE 2
#define STATION 1
#define BROADCAST 0xffffffffffff
#define MAX_DEVICES 32


typedef struct LAN
{
	bridge *bridges;
	station *stations;
	unsigned int nb_bridge;
	unsigned int nb_station;
	graphe *graphe;
}LAN;


void init_Lan(LAN *lan);
void free_Lan(LAN *lan);
void get_config(LAN *lan, const char* filename);
void add_bridge(LAN *lan,bridge *my_bridge);
void add_station(LAN *lan,station *stat);

void receive_frame(station *receiver, frame *message, uint8_t level);
void commute_frame(sommet source, LAN *lan, sommet actuel, frame *message, uint8_t level);
void transfert_frame(sommet source, LAN *lan, frame *message);
void show_stations(LAN *lan);
void show_bridges(LAN *lan);
void show_frame(frame *frame);
void ask_frame(LAN lan);
