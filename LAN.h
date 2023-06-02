#include "commutation.h"
#include "graphe.h"
#include "frame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define BRIDGE 2
#define STATION 1
#define BROADCAST 0xffffffffffff

typedef struct station
{
	uint64_t mac;
	uint32_t ip;
} station;

typedef struct bridge {
	uint64_t mac;
	uint8_t nb_ports;
	uint16_t priority;
	commutation table[64];//table de commutation
} bridge;

typedef struct device
{
	int type;
	int number;	
}device;


typedef struct LAN
{
	bridge *bridges;
	station *stations;
	unsigned int nb_bridge;
	unsigned int nb_station;
	graphe *graphe;
	device *devices;
}LAN;


void init_Lan(LAN *lan);
void free_Lan(LAN *lan);
void get_config(LAN *lan, const char* filename);
void add_bridge(LAN *lan,bridge *my_bridge);
void add_station(LAN *lan,station *stat);
uint64_t build_mac(char* token);
unsigned int str_to_int(char* field);
int power(int nb, int expo);
uint32_t build_ip(char* addr);
void show_devices(LAN *lan);
void print_mac(uint64_t mac);
void print_ip(uint32_t ip);
void receive_frame(station *receiver, frame *message);
void commute_frame(sommet source, LAN *lan, sommet actuel, frame *message, int level);
void transfert_frame(sommet source, LAN *lan, frame *message);
int compare_mac(uint64_t mac1, uint64_t mac2);
void show_stations(LAN *lan);

