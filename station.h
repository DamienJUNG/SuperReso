typedef struct station
{
	byte mac[6];
	byte ip[4];
};

void affiche_mac_station(station maStation);
void affiche_ip_station(station maStation);
void affiche_tout_station(station maStation);