#include <stdio.h>
typedef struct station
{
	unsigned char mac[6];
	unsigned char ip[4];
}station;

void affiche_mac_station(station maStation);
void affiche_ip_station(station maStation);
void affiche_tout_station(station maStation);