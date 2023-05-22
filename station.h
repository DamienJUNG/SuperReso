typedef struct station
{
	unsigned char *mac;
	unsigned char ip[5];
}station;

void affiche_mac_station(station maStation);
void affiche_ip_station(station maStation);
void affiche_tout_station(station maStation);