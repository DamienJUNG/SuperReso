#include "device.h"
#include "commutation.h"
#include "graphe.h"
#include "frame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SWITCH 2
#define STATION 1

typedef struct station
{
	unsigned char mac[6];
	uint8_t ip[4];
}station;

typedef struct Switch {
	unsigned char mac[6];
	unsigned int nb_ports;
	unsigned int priority;
	commutation table[64];//table de commutation
}Switch;


typedef struct LAN
{
	Switch *Switchs;
	station *stations;
	unsigned int Switch_capacite;
	unsigned int station_capacite;
	unsigned int nb_Switch;
	unsigned int nb_station;
	graphe *graphe;
	device *devices;
}LAN;
void init_Lan(LAN *lan);
void free_Lan(LAN *lan);
void get_config(LAN *lan, const char* filename);
void add_Switch(LAN *lan,Switch *my_switch);
void add_station(LAN *lan,station *stat);
void build_mac(char* token,unsigned char* mac);
unsigned int str_to_int(char* field);
int power(int nb, int expo);
void build_ip(char* token, unsigned char* ip);
void show_devices(LAN *lan);
void print_mac(unsigned char* mac);
void print_ip(unsigned char* mac);
void receive_frame(station *receiver, frame *message);
void commute_frame(sommet source, LAN *lan, sommet actuel, frame *message);
void transfert_frame(sommet source, LAN *lan, frame *message);
int compare_mac(unsigned char* mac1, unsigned char *mac2);

